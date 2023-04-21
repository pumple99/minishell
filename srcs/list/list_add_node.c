/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:45:52 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/21 16:46:01 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"
#include <stdlib.h>

static int		get_comp_length(char *np_key, char *cur_node_key);
static void		adding(t_admin *ap, t_node *np);
static void		add_front_loc(t_node *curp, t_node *np);
static void		add_this_loc(t_node *curp, t_node *np);

void	add_node(t_admin *hash_map, char *new_arg)
{
	int		index;
	t_node	*np;

	index = get_index(new_arg);
	np = create_node(new_arg); // new_arg의 내용들을 할당해서 복사함.
	if (hash_map[index].node_cnt == 0)
	{
		hash_map[index].node_cnt++;
		return (add_front_loc(hash_map[index].tail, np));
	}
	adding(&hash_map[index], np);
}

static void	adding(t_admin *ap, t_node *np) // 실제 해쉬 리스트에 추가하는 로직.
{
	t_node	*cur_node;
	int		comp_val;

	cur_node = ap->head->next;
	while (cur_node != ap->tail)
	{
		comp_val = ft_strncmp(np->key, cur_node->key, get_comp_length(np->key, cur_node->key)); // 두개(np->key, cur_node->key) 중 더 긴값에 대해 처리해야함.
		if (comp_val == 0)
			return (add_this_loc(cur_node, np)); // cur 위치에 추가하기.
		else if (comp_val < 0)
			return (ap->node_cnt++, add_front_loc(cur_node, np)); //cur_node의 앞 자리에 추가하기.
		else
			cur_node = cur_node->next;
	}
	return (ap->node_cnt++, add_front_loc(cur_node, np));
}

static int	get_comp_length(char *np_key, char *cur_node_key)
{
	int	np_len;
	int	cur_node_len;
	
	np_len = ft_strlen(np_key);
	cur_node_len = ft_strlen(cur_node_key);
	if (np_len < cur_node_len)
		return (cur_node_len);
	else
		return (np_len);
}

static void	add_front_loc(t_node *curp, t_node *np) // curp노드 앞(head)쪽에 노드 추가하기.
{
	np->prev = curp->prev;
	np->next = curp;
	curp->prev->next = np;
	curp->prev = np;
}

static void	add_this_loc(t_node *curp, t_node *np) // 현재 노드에 값 덮어쓰기.
{
	free(curp->key);
	free(curp->value);
	curp->asm_opr = np->asm_opr;
	curp->key = np->key;
	curp->value = np->value;
	free(np);
}
