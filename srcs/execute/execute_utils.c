/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:27:13 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 19:03:18 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	is_or_and_end(t_token *token)
{
	return (token->type == and || token->type == or || token->type == end);
}

int	is_and_or_pipe_end(t_token *token)
{
	if (token->type == and || token->type == or \
	|| token->type == _pipe || token->type == end)
		return (1);
	else
		return (0);
}

int	is_redirection(t_token *token)
{
	if (token->type == redirect_r || token->type == redirect_l \
	|| token->type == append || token->type == heredoc)
		return (1);
	else
		return (0);
}