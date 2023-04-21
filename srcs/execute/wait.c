/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:19:45 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 20:07:32 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"
#include <stdlib.h>

static void	set_exit_status(int child_status, int *exit_status);
static void	set_questionmark(t_admin *hash_map, int exit_status);

void	wait_last_child(t_admin *hash_map, pid_t last_child_pid, int child_cnt)
{
	int		exit_status;
	int		child_status;
	pid_t	pid_num;

	while (child_cnt--)
	{
		pid_num = wait(&child_status);
		if (pid_num == last_child_pid)
		{
			set_exit_status(child_status, &exit_status);
			set_questionmark(hash_map, exit_status);
		}
	}
}

static void	set_exit_status(int child_status, int *exit_status)
{
	int	status;

	status = 0;
	if (WIFEXITED(child_status))
		status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
		status = WTERMSIG(child_status);
	else if (WIFSTOPPED(child_status))
		status = WSTOPSIG(child_status);
	*exit_status = status;
}

static void	set_questionmark(t_admin *hash_map, int exit_status)
{
	char	*exit_status_char;
	char	*prev_exit_status_char;

	exit_status_char = ft_itoa(exit_status);
	prev_exit_status_char = exit_status_char;
	exit_status_char = ft_strjoin("?=", exit_status_char);
	add_node(hash_map, exit_status_char);
	free(exit_status_char);
	free(prev_exit_status_char);
}
