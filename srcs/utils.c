/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:36:57 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 18:18:41 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	free_double_pointer(char **pptr)
{
	int	i;

	i = -1;
	if (pptr == NULL)
		return ;
	while (pptr[++i])
		free(pptr[i]);
	free(pptr);
}

void	malloc_error(void)
{
	write(2, "Malloc Error\n", 14);
	exit(1);
}
