/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_fd_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:14:09 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 20:21:11 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "safe_function.h"

int	dup_s(int fd)
{
	int	re;

	re = dup(fd);
	if (re == -1)
		perr_exit("minishell: dup failed");
	return (re);
}

int	dup2_s(int fd1, int fd2)
{
	int	re;

	re = dup2(fd1, fd2);
	if (re == -1)
		perr_exit("minishell: dup2 failed");
	return (re);
}

int	close_s(int fd)
{
	int	re;

	re = close(fd);
	if (re == -1)
		perr_exit("minishell: close failed");
	return (re);
}

int	open_s(char *path, int o_flag)
{
	int	re;

	if (o_flag == 0)
		re = open(path, o_flag);
	else
		re = open(path, o_flag, 0644);
	if (re == -1)
		perror("minishell: open failed");
	return (re);
}
