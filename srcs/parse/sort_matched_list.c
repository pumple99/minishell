/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_matched_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:56:26 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/24 20:26:11 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parse.h"

static int	max(int a, int b);

void	sort_matched_result(t_token_list *ml)
{
	t_token	*i;
	t_token	*j;
	char	*str;

	i = ml->head;
	if (i == NULL)
		return ;
	while (i->next != NULL)
	{
		j = ml->head;
		while (j->next != NULL)
		{
			if (ft_strncmp(i->string, j->string, \
				max(ft_strlen(j->string), ft_strlen(j->next->string))) < 0)
			{
				str = j->string;
				j->string = j->next->string;
				j->next->string = str;
			}
			j = j->next;
		}
		i = i->next;
	}
}

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
