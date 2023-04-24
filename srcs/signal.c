/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:06:06 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/24 13:14:24 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
//#include <signal.h>
#include "signal.h"
#include "safe_function.h"

// rl_on_new_line(); 해당 라인의 커서를 맨 앞으로 옮겨주는 함수.
// 	rl_replace_line("", 0); rl_line_buffer을 첫번째 인자로 바꿔주는 함수
// 	rl_redisplay(); prompt를 포함해서 rl_line_buffer을 출력해주는 함수.

void	sigint(void)
{
	write_s(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
