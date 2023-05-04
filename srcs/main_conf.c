/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_conf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:46:32 by sindong-yeo       #+#    #+#             */
/*   Updated: 2023/05/04 14:36:43 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include "safe_function.h"

// rl_on_new_line(); 해당 라인의 커서를 맨 앞으로 옮겨주는 함수.
// 	rl_replace_line("", 0); rl_line_buffer을 첫번째 인자로 바꿔주는 함수
// 	rl_redisplay(); prompt를 포함해서 rl_line_buffer을 출력해주는 함수.
void	sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	write_s(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	config(void)
{
	struct termios	attr;

	tcgetattr(0, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &attr);
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}
