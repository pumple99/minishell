/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_search_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:20:52 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 15:17:59 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"

t_node	*search_node(t_admin *hash_map, char *key)
{
	int		index;
	t_node	*cur_node;

	index = get_index(key);
	if (index == -1)
		return (NULL);
	cur_node = hash_map[index].head->next;
	while (cur_node != hash_map[index].tail)
	{
		if (ft_strncmp(cur_node->key, key, ft_strlen(key)) == 0)
			return (cur_node);
		cur_node = cur_node->next;
	}
	return (NULL);
}
