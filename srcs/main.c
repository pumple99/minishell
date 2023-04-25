/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:01:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/25 18:18:11 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "libft.h"
#include "list.h"
#include "parse.h"
#include "signal.h"
#include "minishell.h"
#include "builtin.h"

void	handler(int signum);

void	config(void)
{
	struct termios	attr;

	tcgetattr(0, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &attr);
}

void	delete_hash_map(t_admin *hash_map)
{
	t_node	*cur_node;
	t_node	*del_node;

	cur_node = hash_map->head->next;
	while (cur_node != hash_map->tail)
	{
		del_node = cur_node;
		cur_node = cur_node->next;
		if (del_node)
			free(del_node);
	}
	if (hash_map->head)
		free(hash_map->head);
	if (hash_map->tail)
		free(hash_map->tail);
	hash_map->node_cnt = 0;
}

void	delete_new_envp(char ***new_envp_ptr)
{
	free_double_pointer(*new_envp_ptr);
	*new_envp_ptr = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line_read;
	t_admin		hash_map[54];
	char		**new_envp;

	new_envp = NULL;
	argc = argc - 1;
	argv = &argv[0];
	config();
	make_hash_map(hash_map, envp, &new_envp);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		line_read = readline("minishell >");
		if (rl_eof_found) // if (rl_eof_found)
		{
			 delete_hash_map(hash_map);
			 delete_new_envp(&new_envp);
			return (0);
		}
		if (*line_read)
			parse_line(hash_map, line_read);
		if (line_read && *line_read)
			add_history (line_read);
		if (line_read)
			free(line_read);
	}
	return (0);
}
