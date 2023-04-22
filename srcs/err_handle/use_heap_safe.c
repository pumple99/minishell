/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_heap_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:07:53 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/22 21:48:57 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include "../../includes/safe_function.h"

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
