/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:25:52 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/17 15:54:17 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static t_token	*find_first_cmd_token(t_token *first_token)
{
	t_token	*token;

	token = first_token;
	while (token->type == redirect_l || token->type == redirect_r || \
	token->type == heredoc || token->type == append)
		token = token->next->next;
	return (token);
}

int	execute_minimal(t_token_list *tl, t_token *token, int is_pipe)
{
	t_token	*first_cmd_token;

	first_cmd_token = find_first_cmd_token(token);
	//execute_redirection
	if (first_cmd_token->type == paren_l)
		return (execute_subshell(first_cmd_token, is_pipe));
	//make char **
	if (is_builtin(first_cmd_token->string))
		return ();
	else
		return ();

	return (0);
}
