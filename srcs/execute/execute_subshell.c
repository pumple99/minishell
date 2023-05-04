/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:53:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:13:32 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "execute.h"
#include "parse.h"
#include "list.h"
#include "minishell.h"
#include "safe_function.h"

static char	**make_argv(char *involve_paren_str);
static char	*get_path_to_execute_minishell(t_admin *hash_map);

int	execute_subshell(t_admin *hash_map, char *involve_paren_str, \
char ***envp, int is_pipe)
{
	pid_t	pid;
	char	**argv;
	char	*path;

	pid = 0;
	if (is_pipe == 0)
		pid = fork_s();
	if (is_pipe || pid == 0)
	{
		argv = make_argv(involve_paren_str);
		path = get_path_to_execute_minishell(hash_map);
		execve_s(path, argv, *envp);
	}
	return (wait_last_child(hash_map, pid, 1));
}

static char	**make_argv(char *involve_paren_str)
{
	char	**argv;

	argv = (char **)malloc_s(sizeof(char *) * 3);
	argv[0] = ft_strdup_s("minishell");
	argv[1] = ft_strdup_s(involve_paren_str);
	argv[2] = NULL;
	return (argv);
}

static char	*get_path_to_execute_minishell(t_admin *hash_map)
{
	t_node	*subshell_path_node;
	char	*path;

	subshell_path_node = search_node(hash_map, "!");
	if (subshell_path_node == NULL)
	{
		write_s(2, "cant execute subshell\n", 23);
		exit (1);
	}
	path = char_join(subshell_path_node->value, "minishell", '/');
	return (path);
}
