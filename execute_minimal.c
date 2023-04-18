/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:25:52 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/18 21:31:56 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	execute_minimal(t_token_list *tl, t_token *token, int is_pipe)
{
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
