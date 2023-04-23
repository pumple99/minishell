/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:24:27 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 17:11:30 by seunghoy         ###   ########.fr       */
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
		close_s(l[0]);
		close_s(l[1]);
	}
	l[0] = r[0];
	l[1] = r[1];
}

static t_token	*get_next_pipe(t_token *token)
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

static void	fd_change(int child_count, t_fds *fds)
{
	if (child_count != 1)
	{
		close_s((fds->left)[1]);
		dup2_s((fds->left)[0], STDIN_FILENO);
	}
	if (child_count != 0)
	{
		close_s((fds->right)[0]);
		dup2_s((fds->right)[1], STDOUT_FILENO);
	}
}

static int	pipe_connect_execute(t_admin *hash_map, char ***envp, \
t_token *token, int child_total)
{
	pid_t	pid;
	int		child_count;
	t_fds	fds;

	child_count = 0;
	pid = 1;
	while (pid != 0 && ++child_count <= child_total)
	{
		if (child_count != 1)
			token = get_next_pipe(token);
		if (child_count != child_total)
			pipe_s(fds.left);
		pid = fork_s();
		if (pid != 0)
			close_left_and_move(fds.left, fds.right, child_count);
	}
	if (pid == 0 && child_count < child_total)
		fd_change(child_count, &fds);
	else if (pid == 0 && child_count == child_total)
		fd_change(0, &fds);
	if (pid == 0)
		return (exit(execute_minimal(hash_map, envp, token, 1)), 0);
	else
		return (wait_last_child(hash_map, pid, child_total));
}

int	execute_pipe(t_admin *hash_map, char ***envp, t_token *token)
{
	int		child_count;
	int		paren_depth;
	t_token	*temp;

	paren_depth = 0;
	temp = token;
	child_count = 1;
	while (temp->type != end)
	{
		if (paren_depth == 0 && is_or_and_end(temp))
			break ;
		if (temp->type == paren_l)
			++paren_depth;
		else if (temp->type == paren_r)
			--paren_depth;
		else if (temp->type == _pipe && paren_depth == 0)
			++child_count;
		temp = temp->next;
	}
	if (child_count == 1)
		return (execute_minimal(hash_map, envp, token, 0));
	else
		return (pipe_connect_execute(hash_map, envp, token, child_count));
}
