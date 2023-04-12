/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:58:56 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/11 16:43:29 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

t_node	*create_node(char *arg)
{
	t_node	*np;
	char	*asm_opr_pos;

	np = (t_node *)malloc(sizeof(t_node));
	if (np == NULL)
	{
			write(2, "Malloc Error", 13);
			exit(1);
	}
	np->prev = NULL;
	np->next = NULL;
	asm_opr_pos = ft_strchr(arg, (int)'=');
	if (asm_opr_pos == NULL) // 대입 연산자 존재 x
	{
		//key만 저장하기.
		np->asm_opr = 0;
		np->key = ft_strdup(arg);
		np->value = NULL;
	}
	else
	{
		//key, value값 저장하기
		np->asm_opr = 1;
		np->key = ft_substr(arg, 0, asm_opr_pos - arg);
		np->value = ft_substr(arg, asm_opr_pos - arg + 1, ft_strlen(asm_opr_pos + 1));
	}
	return (np); // np가 가리키고 있는 주소를 리턴.
}
