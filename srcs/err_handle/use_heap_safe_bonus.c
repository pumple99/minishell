/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_heap_safe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:07:53 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 17:18:04 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/errno.h>
#include "safe_function_bonus.h"

void	*malloc_s(int size_of_container)
{
	void	*re;
	int		prev_errno;

	prev_errno = errno;
	re = malloc(size_of_container);
	if (re == NULL || prev_errno != errno)
		perr_exit("minishell: malloc failed");
	return (re);
}
