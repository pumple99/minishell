/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:01:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:12:19 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft.h"
#include "builtin_bonus.h"
#include "execute_bonus.h"
#include "safe_function_bonus.h"
#include "minishell_bonus.h"

static int	prompt_exec(t_admin *hash_map, char ***new_envp);
static void	meet_eof(t_admin *hash_map);

int	main(int argc, char *argv[], char *envp[])
{
	t_admin	hash_map[55];
	char	**new_envp;

	new_envp = NULL;
	make_hash_map(hash_map, envp, &new_envp);
	if (argc >= 2)
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
			meet_eof(hash_map);
		if (*line_read)
		{
			tl = parse_line(line_read);
			execute(&tl, hash_map, new_envp);
		}
		if (line_read && *line_read)
			add_history (line_read);
		if (line_read)
			free(line_read);
	}
	return (0);
}

static void	meet_eof(t_admin *hash_map)
{
	char	**args;

	args = (char **)malloc_s(sizeof(char *) * 3);
	args[0] = "exit";
	args[1] = ft_strdup(search_node(hash_map, "?")->value);
	args[2] = NULL;
	builtin_exit(hash_map, args);
}
