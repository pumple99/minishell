/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:56:19 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/25 13:15:56 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "builtin.h"
#include "libft.h"
#include "safe_function.h"

int	execute_builtin_cmd(t_admin *hash_map, char ***envp, \
char **minimal_cmd, int builtin_num)
{
	if (builtin_num == cd)
		return (builtin_cd(hash_map, envp, minimal_cmd));
	else if (builtin_num == export)
		return (builtin_export(hash_map, envp, minimal_cmd));
	else if (builtin_num == __exit)
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
		execve_s(cmd_with_path, minimal_cmd, *envp);
	}
	else
	{
		pid = fork_s();
		if (pid == 0)
		{
			if (ft_strlen(minimal_cmd[0]) == 0)
				exit(0);
			path_list = get_path_list_from_env_path(hash_map);
			cmd_with_path = get_path(path_list, minimal_cmd[0]);
			is_executable(cmd_with_path);
			execve_s(cmd_with_path, minimal_cmd, *envp);
		}
		return (wait_last_child(hash_map, pid, 1));
	}
}
