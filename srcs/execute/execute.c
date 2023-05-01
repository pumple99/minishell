/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 20:00:58 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/01 17:51:39 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "execute.h"
#include "safe_function.h"

static t_token	*move_to_and_or_or(t_token *token)
{
	t_token	*temp;
	int		paren_depth;

	paren_depth = 0;
	temp = token;
	if (temp->type == and || temp->type == or)
		temp = temp->next;
	while (temp->type != end)
	{
		if (paren_depth == 0 && is_or_and_end(temp))
			break ;
		if (temp->type == paren_l)
			++paren_depth;
		else if (temp->type == paren_r)
			--paren_depth;
		temp = temp->next;
	}
	return (temp);
}

static void	free_unlink_tl(t_token_list *tl)
{
	t_token	*next;
	t_token	*cur;

	cur = tl->head;
	while (cur->type != end)
	{
		next = cur->next;
		if (cur->type == heredoc)
			unlink_s(next->string);
		free(cur->string);
		free(cur);
		cur = next;
	}
	free(cur);
}

static void	close_dup_stdio(int *stdio_fds)
{
	close_s(stdio_fds[0]);
	close_s(stdio_fds[1]);
}

int	execute(t_token_list *tl, t_admin *hash_map, char ***envp)
{
	t_token	*token;
	int		exit_status;
	int		stdio_fds[2];

	token = tl->head;
	if (token->type == end)
		return (0);
	save_stdio(stdio_fds);
	execute_heredoc(tl);
	exit_status = execute_pipe(hash_map, envp, token);
	restore_stdio(stdio_fds);
	while (token->type != end)
	{
		token = move_to_and_or_or(token);
		if ((exit_status == 0 && token->type == and) \
		|| (exit_status != 0 && token->type == or))
		{
			token = token->next;
			expand_until_or_and_end(hash_map, tl, token);
			exit_status = execute_pipe(hash_map, envp, token);
			restore_stdio(stdio_fds);
		}
	}
	return (close_dup_stdio(stdio_fds), free_unlink_tl(tl), exit_status);
}
