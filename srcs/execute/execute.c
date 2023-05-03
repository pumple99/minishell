/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 20:00:58 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/03 19:31:12 by seunghoy         ###   ########.fr       */
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

	temp = token;
	paren_depth = 0;
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

	if (execute_heredoc(hash_map, tl))
		return (set_questionmark(hash_map, 1), free_unlink_tl(tl), 1);
	save_stdio(stdio_fds);
	expand_until_or_and_end(hash_map, tl, 0);
	exit_status = execute_pipe(hash_map, envp, tl->head);
	restore_stdio(stdio_fds);
	token = tl->head;
	while (token->type != end)
	{
		token = move_to_and_or_or(token);
		if ((exit_status == 0 && token->type == and) \
		|| (exit_status != 0 && token->type == or))
		{
			expand_until_or_and_end(hash_map, tl, token);
			token = token->next;
			exit_status = execute_pipe(hash_map, envp, token);
			restore_stdio(stdio_fds);
		}
	}
	return (close_dup_stdio(stdio_fds), free_unlink_tl(tl), exit_status);
}
