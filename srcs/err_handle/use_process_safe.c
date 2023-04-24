/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_process_safe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:19:25 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/24 20:38:32 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
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

int	execve_s(const char *path, char *const argv[], char *const envp[])
{
	int	re;

	re = execve(path, argv, envp);
	if (re == -1)
		perror("minishell: execve failed");
	return (re);
}
