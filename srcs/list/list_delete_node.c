/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delete_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:26:46 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/03 20:09:01 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

void	delete_node(t_admin *hash_map, char *key, int *re_build_flag)
{
	int		index;
	t_node	*del_node;

	index = get_index(key);
	if (index == -1)
		return ;
	del_node = search_node(hash_map, key);
	if (del_node == NULL)
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
