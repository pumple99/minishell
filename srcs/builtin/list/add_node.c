/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:45:52 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/06 16:16:08 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		get_index(t_node *np);
static void		adding(t_admin *ap, t_node *np);
static void		add_front_loc(t_node *curp, t_node *np);
static void		add_this_loc(t_node *curp, t_node *np);

void	add_node(t_admin *hash_map, char *new_arg)
{
	int		index;
	t_node	*np;

	np = create_node(new_arg);
	index = get_index(np);
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
	int		val;
	
	cur_node = ap->head->next;
	while (cur_node != ap->tail)
	{
		val = ft_strncmp(np->key, cur_node->key, ft_strlen(np->key));
		if (val == 0)
			return (add_this_loc(cur_node, np)); // cur 위치에 추가하기.
		else if (val < 0)
			return (ap->node_cnt++, add_front_loc(cur_node, np)); //cur_node의 앞 자리에 추가하기.
		else
			cur_node = cur_node->next;
	}
	return (ap->node_cnt++, add_front_loc(cur_node, np));
}

static int		get_index(t_node *np) // hash_map의 몇번째 인덱스 리스트에 추가할지 정하기.
{
	char	region;
	int		index;

	region = np->key[0] - 'A';
	if (0 <= region && region <= 26)
		index = region;
	else if (region == 31)
		index = 53;
	else
		index = np->key[0] - 'a' + 26;
	return (index);
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
	curp->key = np->key;
	curp->value = np->value;
	free(np);
}
