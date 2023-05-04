/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:19:45 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 15:49:19 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "execute.h"

static int	set_exit_status(int child_status);

int	wait_last_child(t_admin *hash_map, pid_t last_child_pid, int child_cnt)
{
	int		exit_status;
	int		child_status;
	pid_t	pid_num;

	exit_status = 0;
	while (child_cnt--)
	{
		pid_num = wait(&child_status);
		if (pid_num == last_child_pid)
		{
			exit_status = set_exit_status(child_status);
			set_questionmark(hash_map, exit_status);
		}
	}
	return (exit_status);
}

static int	set_exit_status(int child_status)
{
	int	status;

	status = 0;
	if (WIFEXITED(child_status))
		status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
		status = WTERMSIG(child_status) + 128;
	else if (WIFSTOPPED(child_status))
		status = WSTOPSIG(child_status);
	return (status);
}
