/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:27:13 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:13:32 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"
#include "safe_function_bonus.h"

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

void	save_stdio(int *stdio_fds)
{
	stdio_fds[0] = dup_s(STDIN_FILENO);
	stdio_fds[1] = dup_s(STDOUT_FILENO);
}

void	restore_stdio(int *stdio_fds)
{
	dup2_s(stdio_fds[0], STDIN_FILENO);
	dup2_s(stdio_fds[1], STDOUT_FILENO);
}
