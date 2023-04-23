/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:09:57 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 23:44:49 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

void	perr_exit(char *str)
{
	perror(str);
	exit(errno);
}

void	malloc_error(void)
{
	perror("minishell: malloc failed");
	exit(errno);
}
