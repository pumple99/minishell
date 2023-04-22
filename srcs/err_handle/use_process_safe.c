/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_process_safe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:19:25 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/22 21:33:45 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "safe_function.h"

int	pipe_s(int *fildes)
{
	int	re;

	re = pipe(fildes);
	if (re == -1)
		perr_exit("minishell: pipe failed");
	return (re);
}

pid_t	fork_s(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perr_exit("minishell: fork failed");
	return (pid);
}
