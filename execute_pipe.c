/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:24:27 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/16 21:55:51 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	make_pipe_and_execute_minimal(t_token_list *tl, t_token *token)
{
	return (0);
}

int	execute_pipe(t_token_list *tl, t_token *token)
{
	int		pipe_count;
	int		paren_depth;
	t_token	*temp;

	paren_depth = 0;
	temp = token;
	pipe_count = 0;
	while (temp->type != end)
	{
		if (paren_depth == 0 && is_or_and_end(temp))
			break;
		if (token->type == paren_l)
			++paren_depth;
		else if (token->type == paren_r)
			--paren_depth;
		else if (token->type == _pipe && paren_depth == 0)
			++pipe_count;
		temp = temp->next;
	}
	if (pipe_count == 0)
		return (execute_minimal(tl, token, 0));
	else
		return (make_pipe_and_execute_minimal(tl, token));
}