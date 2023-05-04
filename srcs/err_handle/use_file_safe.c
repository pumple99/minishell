/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_file_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:34:39 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/03 19:41:09 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	unlink_s(char *path)
{
	int	re;

	if (access(path, F_OK) != 0)
		return (0);
	re = unlink(path);
	if (re == -1)
		perror("minishell: unlink failed");
	return (re);
}
