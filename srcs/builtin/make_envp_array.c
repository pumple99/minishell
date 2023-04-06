/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:21:27 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/06 16:37:53 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void	free_prev_envp(char ***envp);
static int	get_array_size(t_admin *hash_map);

void	make_array(t_admin *hash_map, char ***envp)
{
	int 	hash_map_index;
	int		envp_index;
	int		array_size;
	char	*str;
	t_node	*cur_node;

	free_prev_envp(envp);
	array_size = get_array_size(hash_map);
	(*envp) = (char **)malloc(sizeof(char *) * (array_size + 1));
	if (*envp == NULL)
	{
		write(2, "Malloc Error", 13);
		exit(1);
	}
	(*envp)[array_size] = NULL;
	hash_map_index = -1;
	envp_index = -1;
	while(++hash_map_index <= 52)
	{
		cur_node = hash_map[hash_map_index].head->next;
		while (cur_node != hash_map[hash_map_index].tail)
		{
			if (cur_node->asm_opr == 1)
			{
				str = ft_strjoin(cur_node->key, "=");
				(*envp)[++envp_index] = ft_strjoin(str, cur_node->value);
				free(str);
			}
			cur_node = cur_node->next;
		}
	}
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
			if (cur_node->asm_opr == 1)
				array_size++;
			cur_node = cur_node->next;
		}
	}
	return (array_size);
}

static void	free_prev_envp(char ***envp)
{
	int	i;

	if (*envp == NULL)
		return ;
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}
