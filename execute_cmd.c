/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:56:19 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/20 18:59:50 by dongyshi         ###   ########.fr       */
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
	char	*cmd_with_path;
	char	**path_list;
	pid_t	pid;

	path_list = get_path_list_from_env_path(hash_map); // 2차원 배열로 하나 생성하기.
	if (is_pipe) // is_pipe == 1 => 이미 fork가 되어있는 상태. 그냥 실행하기
	{
		cmd_with_path = get_path(path_list, minimal_cmd[0]);
		is_executable(cmd_with_path);
		execve(cmd_with_path, minimal_cmd, *envp);
	}
	else // is_pipe == 0 => fork가 되어있지 않은 상태. fork후 실행하기.
	{
		pid = fork();
		// if (fork < -1)
		// 	error handling
		if (pid == 0)
		{
			cmd_with_path = get_path(path_list, minimal_cmd[0]);
			is_executable(cmd_with_path);
			execve(cmd_with_path, minimal_cmd, *envp);
		}
	}
	free(cmd_with_path);
	free_double_pointer(path_list);
}
