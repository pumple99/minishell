/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:27:13 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/16 21:46:59 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	is_not_or_and_end(t_token *token)
{
	return (token->type == and || token->type == or || token->type == end);
}

int	is_not_and_or_end(t_token *token)
{
	return (token->type != and && token->type != or && token->type != end);
}

int	is_not_and_or_end_pipe(t_token *token)
{
	return (token->type != _pipe && token->type != and \
	&& token->type != or && token->type != end);
}