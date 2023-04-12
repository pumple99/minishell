/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:01:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 19:55:11 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <termios.h>

void	sigint(void)
{
	write(1, "\n", 1);
	rl_on_new_line(); // 해당 라인의 커서를 맨 앞으로 옮겨주는 함수.
	rl_replace_line("", 0); // rl_line_buffer을 첫번째 인자로 바꿔주는 함수
	rl_redisplay(); // prompt를 포함해서 rl_line_buffer을 출력해주는 함수.
	return ;
}

void	sigquit(void)
{
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	handler(int signum)
{
	if (signum == SIGINT)
		sigint();
	else if (signum == SIGQUIT)
		sigquit();
}

int	main(int argc, char *argv[], char *envp[])
{
	struct termios	attr;
	char			*line_read;
	t_admin			hash_map[53];
	char			**new_envp;

	argc = 0;
	argv = 0;
	make_hash_map(hash_map, envp, &new_envp);
	tcgetattr(0, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &attr);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		line_read = readline("minishell >");
		if (line_read && *line_read)
			add_history (line_read);
		if (rl_eof_found)
		{
			free(line_read);
			return (0);
		}
		free(line_read);
	}
	return (0);
}
