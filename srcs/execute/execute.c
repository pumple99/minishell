/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 20:00:58 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 15:52:33 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/parse.h"

static t_token	*move_to_and_or_or(t_token *token)
{
	t_token	*temp;
	int		paren_depth;

	paren_depth = 0;
	temp = token;
	while (temp->type != end)
	{
		if (paren_depth == 0 && is_or_and_end(temp))
			break;
		if (token->type == paren_l)
			++paren_depth;
		else if (token->type == paren_r)
			--paren_depth;
		temp = temp->next;
	}
	return (temp);
}

static void	save_stdio(int *stdio_fds)
{
	if (stdio_fds[0] == 0 && stdio_fds[1] == 0)
	{
		stdio_fds[0] = check_dup(STDIN);
		stdio_fds[1] = check_dup(STDOUT);
	}
}

static void	restore_stdio(int *stdio_fds)
{
	check_dup2(stdio_fds[0], STDIN);
	check_dup2(stdio_fds[1], STDOUT);
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
			unlink(next->string);
		free(cur->string);
		free(cur);
		cur = next;
	}
	free(cur);
}

void	execute(t_token_list *tl)
{
	t_token			*token;
	int				exit_status;
	static int		stdio_fds[2];

	token = tl->head;
	if (token->type != end)
	{
		save_stdio(stdio_fds);
		execute_heredoc(tl);
		exit_status = execute_pipe(token);
		restore_stdio(stdio_fds);
		while (token->type != end)
		{
			token = move_to_and_or_or(token);
			if ((exit_status == 0 && token->type == and) \
			|| (exit_status != 0 && token->type == or))
			{
				token = token->next;
				exit_status = execute_pipe(token);
				restore_stdio(stdio_fds);
			}
		}
	}
	free_unlink_tl(tl);
}
