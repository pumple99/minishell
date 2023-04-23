/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:36:57 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 19:17:57 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "safe_function.h"

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

char	*char_join(char *s1, char *s2, char c)
{
	size_t	len1;
	size_t	len2;
	size_t	idx;
	char	*sj;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	sj = (char *)malloc_s(len1 + len2 + 2);
	idx = -1;
	while (++idx < len1)
		sj[idx] = s1[idx];
	sj[idx] = c;
	idx = -1;
	while (++idx < len2)
		sj[len1 + 1 + idx] = s2[idx];
	sj[len1 + 1 + len2] = 0;
	return (sj);
}
