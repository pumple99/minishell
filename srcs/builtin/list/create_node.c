/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:58:56 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/06 16:39:11 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_node	*create_node(char	*export_arg)
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
	asm_opr_pos = ft_strchr(export_arg, (int)'=');
	if (asm_opr_pos == 0) // 대입 연산자 존재 x
	{
		//key만 저장하기.
		np->asm_opr = 0;
		np->key = ft_strdup(export_arg);
		np->value = NULL;
	}
	else
	{
		//key, value값 저장하기
		np->asm_opr = 1;
		np->key = ft_substr(export_arg, 0, asm_opr_pos - export_arg);
		np->value = ft_substr(export_arg, asm_opr_pos - export_arg + 1, ft_strlen(asm_opr_pos + 1));
	}
	return (np); // np가 가리키고 있는 주소를 리턴.
}
