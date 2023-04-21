/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 20:00:58 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/20 22:49:21 by seunghoy         ###   ########.fr       */
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

void	execute(t_token_list *tl)
{
	t_token	*token;
	int		exit_status;

	token = tl->head;
	if (token->type != end)
	{
		execute_heredoc(tl);
		exit_status = execute_pipe(token);
		while (token->type != end)
		{
			token = move_to_and_or_or(token);
			if ((exit_status == 0 && token->type == and) \
			|| (exit_status != 0 && token->type == or))
			{
				token = token->next;
				exit_status = execute_pipe(token);
			}
		}
	}
	free_unlink_tl(tl);
}

void	free_unlink_tl(t_token_list *tl)
{
	t_token	*next;
	t_token	*cur;

	check_dup2(saved_stdout, STDOUT);
	check_dup2(saved_stdin, STDIN);
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