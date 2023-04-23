/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:21:27 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 01:03:48 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "list.h"
#include "libft.h"
#include "minishell.h"
#include "safe_function.h"

static int	get_array_size(t_admin *hash_map);
static void	fill_array(t_admin *hash_map, char ***envp);

void	make_new_envp(t_admin *hash_map, char ***envp)
{
	int	array_size;

	free_double_pointer(*envp);
	array_size = get_array_size(hash_map);
	(*envp) = (char **)malloc_s(sizeof(char *) * (array_size + 1));
	fill_array(hash_map, envp);
	(*envp)[array_size] = NULL;
}

static int	get_array_size(t_admin *hash_map)
{
	int		i;
	int		array_size;
	t_node	*cur_node;

	i = -1;
	array_size = 0;
	while(++i <= 52)
	{
		cur_node = hash_map[i].head->next;
		while (cur_node != hash_map[i].tail)
		{
			if (cur_node->asm_opr == 1) // assignment operator가 있으면 배열에 추가하기.
				array_size++;
			cur_node = cur_node->next;
		}
	}
	return (array_size);
}

static void	fill_array(t_admin *hash_map, char ***envp)
{
	int		envp_index;
	int		hash_map_index;
	t_node	*cur_node;
	
	envp_index = -1;
	hash_map_index = -1;
	while(++hash_map_index <= 52)
	{
		cur_node = hash_map[hash_map_index].head->next;
		while (cur_node != hash_map[hash_map_index].tail)
		{
			if (cur_node->asm_opr == 1)
				(*envp)[++envp_index] = \
				char_join(cur_node->key, cur_node->value, '=');
			cur_node = cur_node->next;
		}
	}
}
