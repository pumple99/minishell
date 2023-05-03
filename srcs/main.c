/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:01:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/03 19:48:19 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "list.h"
#include "parse.h"
#include "builtin.h"
#include "execute.h"
#include "minishell.h"

static int	prompt_exec(t_admin *hash_map, char ***new_envp);

//void	func()
//{
//	system("leaks minishell");
//}
//atexit(func);
int	main(int argc, char *argv[], char *envp[])
{
	t_admin	hash_map[55];
	char	**new_envp;

	new_envp = NULL;
	make_hash_map(hash_map, envp, &new_envp);
	is_exec_subshell(hash_map, argv, &new_envp);
	config();
	return (prompt_exec(hash_map, &new_envp));
}

static int	prompt_exec(t_admin *hash_map, char ***new_envp)
{
	t_token_list	tl;
	char			*line_read;

	while (1)
	{
		signal(SIGINT, sigint);
		line_read = readline("minishell> ");
		if (rl_eof_found)
		{
			delete_hash_map(hash_map);
			delete_new_envp(new_envp);
			free(line_read);
			return (1);
		}
		if (*line_read)
		{
			tl = parse_line(hash_map, line_read);
			execute(&tl, hash_map, new_envp);
		}
		if (line_read && *line_read)
			add_history (line_read);
		if (line_read)
			free(line_read);
	}
	return (0);
}
