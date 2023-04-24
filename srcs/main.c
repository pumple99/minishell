/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:01:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/24 21:34:49 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <readline/history.h>
#include <readline/readline.h>

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

int	main(int argc, char *argv[], char *envp[])
{
	char		*line_read;
	t_admin		hash_map[53];
	char		**new_envp;

	new_envp = NULL;
	argc = 0;
	argv = 0;
	config();
	make_hash_map(hash_map, envp, &new_envp);
	while (1)
	{
		signal(SIGINT, handler); // 시그널 처리 오류 -> ctrl c누르면 새로운 프롬프트 띄우기
		signal(SIGQUIT, handler); // 시그널 처리 오류 -> ctrl '\' 누르면 문자 아무것도 없으면 새 프롬프트 있으면 아무것도 동작 x
		line_read = readline("minishell >");
		//parse_line(hash_map, line_read); // 개행 들어오면 에러
		if (line_read && *line_read)
			add_history (line_read);
		if (rl_eof_found) // 오류 나는 부분 -> 종료가 되기는 하는데 abort가 뜸.
			return (free(line_read), 0);
		if (line_read)
		{
			free(line_read);
			line_read = NULL;
		}
	}
	return (0);
}
