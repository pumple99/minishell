/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:56:19 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 15:48:31 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int	execute_builtin_cmd(t_admin *hash_map, char ***envp, \
char **minimal_cmd, int builtin_num)
{
	if (builtin_num == cd)
		return (builtin_cd(hash_map, envp, minimal_cmd));
	else if (builtin_num == export)
		return (builtin_export(hash_map, envp, minimal_cmd));
	else if (builtin_num == _exit)
		return (builtin_exit(minimal_cmd));
	else if (builtin_num == echo)
		return (builtin_echo(minimal_cmd));
	else if (builtin_num == env)
		return (builtin_env(envp));
	else if (builtin_num == pwd)
		return (builtin_pwd(hash_map));
	else
		return (builtin_unset(hash_map, envp, minimal_cmd));
}

int	execute_non_builtin_cmd(t_admin *hash_map, char ***envp, \
char **minimal_cmd, int is_pipe)
{
	char	**path_list;
	char	*cmd_with_path;
	pid_t	pid;

	if (is_pipe)
	{
		if (ft_strlen(minimal_cmd[0]) == 0)
			exit(0);
		path_list = get_path_list_from_env_path(hash_map); 
		cmd_with_path = get_path(path_list, minimal_cmd[0]);
		is_executable(cmd_with_path);
		execve(cmd_with_path, minimal_cmd, *envp); //execve가 에러가 나면?
	}
	else
	{
		pid = fork_s();
		// if (fork < -1)
		// 	error handling
		if (pid == 0)
		{
			if (ft_strlen(minimal_cmd[0]) == 0)
				exit(0);
			path_list = get_path_list_from_env_path(hash_map);
			cmd_with_path = get_path(path_list, minimal_cmd[0]);
			is_executable(cmd_with_path);
			execve(cmd_with_path, minimal_cmd, *envp); //execve가 에러가 나면?
		}
		wait_last_child(hash_map, pid, 1);
	}
}
