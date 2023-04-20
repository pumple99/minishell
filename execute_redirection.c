/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:36:09 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/20 22:46:29 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static void	change_fd(t_token *redirect_token)
{
	int		fd;
	char	*str;

	str = redirect_token->next->string;
	if (redirect_token->type == redirect_l || redirect_token->type == heredoc)
	{
		fd = check_open(str, O_RDONLY);
		check_dup2(fd, STDIN);
	}
	else if (redirect_token->type == redirect_r)
	{
		fd = check_open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		check_dup2(fd, STDOUT);
	}
	else if (redirect_token->type == append)
	{
		fd = check_open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		check_dup2(fd, STDOUT);
	}
}

static int	is_ambiguous(t_token *redirect_token)
{
	if (redirect_token->type == heredoc)
		return (0);
	if (redirect_token->next->expand == wild_card)
		return (1);
	return (0);
}

int	execute_redirection(t_token *token)
{
	t_token	*temp;
	int		paren_depth;

	paren_depth = 0;
	temp = token;
	while (temp->type != end)
	{
		if (paren_depth == 0 && is_redirection(temp))
		{
			if (is_ambiguous(temp))
				return (1);
			change_fd(temp);
			temp = temp->next->next;
		}
		if (paren_depth == 0 && is_and_or_pipe_end(temp))
			break;
		if (temp->type == paren_l)
			++paren_depth;
		else if (temp->type == paren_r)
			--paren_depth;
		temp = temp->next;
	}
	return (0);
}