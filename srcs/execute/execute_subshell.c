/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:53:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 15:54:09 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../includes/parse.h"
#include <unistd.h>

static char	**make_argv(char *involve_paren_str);
static char	*get_path_to_execute_minishell(void);

int	execute_subshell(char *involve_paren_str, char ***envp, int is_pipe)
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
		pid = fork();
		// if (pid < 0)
			// error handling
		if (pid == 0)
		{
			argv = make_argv(involve_paren_str);
			path = get_path_to_execute_minishell();
			execve(path, argv, *envp); //execve가 에러가 나면?
		}
	}
}

static char	**make_argv(char *involve_paren_str)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * 3);
	if (argv == NULL)
		malloc_error();
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

	pwd = getcwd(NULL, 0);
	// if (pwd == NULL)
		// error handling
	path = char_join(pwd, "minishell", '/');
	if (path == NULL)
		malloc_error();
	return (path);
}