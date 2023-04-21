/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:36:09 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 21:16:46 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/parse.h"
#include "includes/execute.h"

static void	add_fd_to_list(t_fd_list *fd_list, int fd)
{
	t_fd_node	*node;

	node = (t_fd_node *)malloc(sizeof(t_fd_node));
	node->fd = fd;
	node->next = fd_list->first_node;
	fd_list->first_node = node;
}

static int	change_fd(t_token *redirect_token, t_fd_list *fd_list)
{
	int		fd;
	char	*str;

	str = redirect_token->next->string;
	if (is_ambiguous(redirect_token))
		return (fd_list->err = 1, 1);
	if (redirect_token->type == redirect_r)
	{
		fd = check_open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		check_dup2(fd, STDOUT);
	}
	else if (redirect_token->type == append)
	{
		fd = check_open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		check_dup2(fd, STDOUT);
	}
	else
	{
		fd = check_open(str, O_RDONLY);
		if (fd == -1)
			return (fd_list->err = 1, 1);
		check_dup2(fd, STDIN);
	}
	return (add_fd_to_list(fd_list, fd), 0);
}

static int	is_ambiguous(t_token *redirect_token)
{
	if (redirect_token->type == heredoc)
		return (0);
	if (redirect_token->next->expand == wild_card)
	{
		write(2, "minishell: ambiguous redirect\n", 30);
		return (1);
	}
	return (0);
}

t_fd_list	execute_redirection(t_token *token)
{
	t_token		*temp;
	int			paren_depth;
	t_fd_list	fd_list;

	fd_list.err = 0;
	fd_list.first_node = 0;
	paren_depth = 0;
	temp = token;
	while (paren_depth != 0 || !is_and_or_pipe_end(temp))
	{
		if (paren_depth == 0 && is_redirection(temp))
		{
			if (change_fd(temp, &fd_list))
				return (fd_list);
			temp = temp->next->next;
		}
		if (temp->type == paren_l)
			++paren_depth;
		else if (temp->type == paren_r)
			--paren_depth;
		temp = temp->next;
	}
	return (fd_list);
}

int	close_redirect_fds(t_fd_list fd_list, int re)
{
	t_fd_node	*node;

	node = fd_list.first_node;
	while (node)
	{
		close_s(node->fd);
		node = node->next;
	}
	return (re);
}
