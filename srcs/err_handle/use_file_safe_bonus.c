/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_file_safe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:34:39 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:13:09 by dongyshi         ###   ########.fr       */
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
