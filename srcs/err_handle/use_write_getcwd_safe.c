/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_write_getcwd_safe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:07:20 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 20:22:25 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*getcwd_s(char *buf, size_t size)
{
	char	*re;

	re = getcwd(buf, size);
	if (re == NULL)
		perror("minishell: getcwd failed");
	return (re);
}

int	write_s(int fd, const char *str, int _strlen)
{
	int	re;

	re = write(fd, str, _strlen);
	if (re != _strlen)
		perror("minishell: write failed");
	return (re);
}
