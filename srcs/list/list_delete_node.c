/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delete_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:46 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/10 17:48:30 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

void	delete_node(t_admin *hash_map, char *key, int *re_build_flag)
{
	int		index;
	int		find_flag;
	t_node	*del_node;

	find_flag = 0;
	index = get_index(key);
	del_node = search_node(hash_map, key);
	if (del_node == NULL) // 삭제할 arg와 일치하는 노드가 존재하지 않는 경우.
		return ;
	else
	{
		*re_build_flag = 1;
		hash_map[index].node_cnt--;
		del_node->prev->next = del_node->next;
		del_node->next->prev = del_node->prev;
		free(del_node->key);
		free(del_node->value);
	}

}