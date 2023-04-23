/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_file_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:34:39 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 20:21:21 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	unlink_s(char *path)
{
	int	re;

	re = unlink(path);
	if (re == -1)
		perror("minishell: unlink failed");
	return (re);
}
