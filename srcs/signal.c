/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:06:06 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 15:58:19 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

void	sigint(void)
{
	write_s(1, "\n", 1);
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
