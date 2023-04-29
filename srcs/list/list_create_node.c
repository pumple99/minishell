/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:58:56 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/29 17:49:32 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "list.h"
#include "libft.h"
#include "safe_function.h"

t_node	*create_node(char *arg)
{
	t_node	*np;
	char	*asm_opr_pos;

	np = (t_node *)malloc_s(sizeof(t_node));
	np->prev = NULL;
	np->next = NULL;
	asm_opr_pos = ft_strchr(arg, (int) '=');
	if (asm_opr_pos == NULL)
	{
		np->asm_opr = 0;
		np->key = ft_strdup_s(arg);
		np->value = NULL;
	}
	else
	{
		np->asm_opr = 1;
		np->key = ft_substr_s(arg, 0, asm_opr_pos - arg);
		np->value = ft_substr_s(arg, asm_opr_pos - arg + 1, \
		ft_strlen(asm_opr_pos + 1));
	}
	return (np);
}
