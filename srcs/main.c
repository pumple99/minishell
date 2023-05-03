/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:01:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/02 21:07:52 by sindong-yeo      ###   ########.fr       */
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

//void	func()
//{
//	system("leaks minishell");
//}

int	main(int argc, char *argv[], char *envp[])
{
	//atexit(func);
	char			*line_read;
	t_admin			hash_map[55];
	char			**new_envp;
	t_token_list	tl;
	int				exit_status;

	new_envp = NULL;
	make_hash_map(hash_map, envp, &new_envp);
	is_exec_subshell(hash_map, argv, &new_envp);
	config();
	while (1)
	{
		signal(SIGINT, sigint);
		line_read = readline("minishell> ");
		if (rl_eof_found)
		{
			delete_hash_map(hash_map);
			delete_new_envp(&new_envp);
			free(line_read);
			return (0);
		}
		if (*line_read)
		{
			tl = parse_line(hash_map, line_read);
			exit_status = execute(&tl, hash_map, &new_envp);
		}
		if (line_read && *line_read)
			add_history (line_read);
		if (line_read)
			free(line_read);
	}
	return (0);
}
