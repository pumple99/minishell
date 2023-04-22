/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_file_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:34:39 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/22 21:41:08 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	unlink_s(char *path)
{
	int	re;

	re = unlink(path);
	if (re == -1)
		perror("minishell: unlink failed");
	return (re);
}
