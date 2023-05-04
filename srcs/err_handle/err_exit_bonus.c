/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:09:57 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 17:20:34 by dongyshi         ###   ########.fr       */
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
