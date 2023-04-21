/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_fd_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:14:09 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 18:33:50 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/safe_function.h"

int	dup_s(int fd)
{
	int	re;

	re = dup(fd);
	if (re != -1)
		return (re);
	perr_exit("minishell: dup failed");
}

int	dup2_s(int fd1, int fd2)
{
	int	re;

	re = dup2(fd1, fd2);
	if (re != -1)
		return (re);
	perr_exit("minishell: dup2 failed");
}

int	close_s(int fd)
{
	int	re;

	re = close(fd);
	if (re != -1)
		return (re);
	perr_exit("minishell: close failed");
}