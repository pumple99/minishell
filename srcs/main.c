/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:01:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/24 14:08:27 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "list.h"
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

int	main(int argc, char *argv[], char *envp[])
{
	char		*line_read;
	t_admin		hash_map[53];
	char		**new_envp;

	argc = 0;
	argv = 0;
	config();
	make_hash_map(hash_map, envp, &new_envp);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		line_read = readline("minishell >");
		if (line_read && *line_read != ' ')
			add_history (line_read);
		if (rl_eof_found)
			return (free(line_read), 0);
		free(line_read);
	}
	return (0);
}
