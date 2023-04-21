/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:24:27 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 19:16:40 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/parse.h"
#include "../includes/execute.h"

static void	close_left_and_move(int *l, int *r, int count)
{
	if (count != 1)
	{
		check_close(l[0]);
		check_close(l[1]);
	}
	l[0] = r[0];
	l[1] = r[1];
}

t_token	*get_next_pipe(t_token *token)
{
	int		paren_depth;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && is_or_and_end(token))
			return (0);
		if (token->type == paren_l)
			++paren_depth;
		else if (token->type == paren_r)
			--paren_depth;
		else if (token->type == _pipe && paren_depth == 0)
			return (token->next);
		token = token->next;
	}
}

void	fd_change(int pipe_count, t_fds *fds)
{
	if (pipe_count != 1)
	{
		check_close((fds->left)[1]);
		check_dup2((fds->left)[0], STDIN);
	}
	if (pipe_count != 0)
	{
		check_close((fds->right)[0]);
		check_dup2((fds->right)[1], STDOUT);
	}
}

int	make_pipe_and_execute_minimal(t_token *token, int pipe_total)
{
	pid_t	pid;
	int		pipe_count;
	t_fds	fds;

	pipe_count = 0;
	pid = 1;
	while (pid != 0 && ++pipe_count <= pipe_total)
	{
		if (pipe_count != 1)
			token = get_next_pipe(token);
		if (pipe_count != pipe_total)
			check_pipe(fds.left);
		pid = check_fork();
		if (pid != 0)
			close_left_and_move(fds.left, fds.right, pipe_count);
	}
	if (pid == 0 && pipe_count < pipe_total)
		fd_change(pipe_count, &fds);
	else if (pid == 0 && pipe_count == pipe_total)
		fd_change(0, &fds);
	if (pid == 0)
		return (exit(execute_minimal()));
	else
		return (wait());
}

int	execute_pipe(t_token *token)
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
		if (temp->type == paren_l)
			++paren_depth;
		else if (temp->type == paren_r)
			--paren_depth;
		else if (temp->type == _pipe && paren_depth == 0)
			++pipe_count;
		temp = temp->next;
	}
	if (pipe_count == 0)
		return (execute_minimal(tl, token, 0));
	else
		return (make_pipe_and_execute_minimal(token, pipe_count));
}