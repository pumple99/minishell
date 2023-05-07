/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_fd_safe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:14:09 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/07 23:11:15 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "safe_function_bonus.h"
#include "libft.h"

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
	{
		write_s(2, "minishell: ", 12);
		write_s(2, path, ft_strlen(path));
		write_s(2, ": ", 2);
		perror("");
	}
	return (re);
}
