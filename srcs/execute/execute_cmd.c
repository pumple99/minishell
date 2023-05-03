/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:56:19 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/03 20:02:07 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "builtin.h"
#include "signal.h"
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
		return (builtin_exit(hash_map, minimal_cmd));
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

	pid = 0;
	signal(SIGINT, SIG_IGN);
	if (is_pipe == 0)
		pid = fork_s();
	if (is_pipe || pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ft_strlen(minimal_cmd[0]) == 0)
			is_executable(minimal_cmd[0]);
		path_list = get_path_list_from_env_path(hash_map);
		cmd_with_path = get_path(path_list, minimal_cmd[0]);
		is_executable(cmd_with_path);
		execve_s(cmd_with_path, minimal_cmd, *envp);
	}
	return (wait_last_child(hash_map, pid, 1));
}
