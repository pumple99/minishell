/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_matched_list_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:56:26 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:38 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse_bonus.h"

static int	max(int a, int b);

void	sort_matched_result(t_token_list *ml)
{
	t_token	*i;
	t_token	*j;
	char	*str;

	if (ml->head == NULL)
		return ;
	i = ml->head;
	while (i->next != NULL)
	{
		j = ml->head;
		while (j->next != NULL)
		{
			if (ft_strncmp(j->string, j->next->string, \
				max(ft_strlen(j->string), ft_strlen(j->next->string))) > 0)
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
