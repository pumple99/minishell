/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:53:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 19:20:30 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "execute_bonus.h"
#include "../includes/parse_bonus.h"
#include "list.h"
#include "safe_function.h"

static char	**make_argv(char *involve_paren_str);
static char	*get_path_to_execute_minishell(void);

int	execute_subshell(t_admin *hash_map, char *involve_paren_str, \
char ***envp, int is_pipe)
{
	pid_t	pid;
	char	**argv;
	char	*path;

	if (is_pipe)
	{
		argv = make_argv(involve_paren_str);
		path = get_path_to_execute_minishell();
		execve(path, argv, *envp); //execve가 에러가 나면?
	}
	else
	{
		pid = fork_s();
		if (pid == 0)
		{
			argv = make_argv(involve_paren_str);
			path = get_path_to_execute_minishell();
			execve(path, argv, *envp); //execve가 에러가 나면?
		}
		wait_last_child(hash_map, pid, 1);
	}
}

static char	**make_argv(char *involve_paren_str)
{
	char	**argv;

	argv = (char **)malloc_s(sizeof(char *) * 3);
	argv[0] = ft_strdup("minishell");
	if (argv[0] == NULL)
		malloc_error();
	argv[1] = ft_strdup(involve_paren_str);
	if (argv[1] == NULL)
		malloc_error();
	argv[2] = '\0';
}

static char	*get_path_to_execute_minishell(void)
{
	char	*path;
	char	*pwd;

	pwd = getcwd_s(NULL, 0);
	path = char_join(pwd, "minishell", '/');
	return (path);
}
