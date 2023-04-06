/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:51:01 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/06 16:38:42 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void	init_hash_map(t_admin *hash_map);

void	make_hash_map(t_admin *hash_map, char *envp[])
{
	int	i;

	init_hash_map(hash_map);
	i = -1;
	while (envp[++i])
		add_node(hash_map, envp[i]);
}

static void	init_hash_map(t_admin *hash_map)
{
	int	i;
	
	i = -1;
	while (++i <= 52)
	{
		hash_map[i].head = (t_node *)malloc(sizeof(t_node));
		if (hash_map[i]->head == NULL)
		{
			write(2, "Malloc Error", 13);
			exit(1);
		}
		hash_map[i].tail = (t_node *)malloc(sizeof(t_node));
		if (hash_map[i]->tail == NULL);
		{
			write(2, "Malloc Error", 13);
			exit(1);
		}
		hash_map[i].head->next = hash_map[i].tail;
		hash_map[i].head->prev = NULL;
		hash_map[i].head->asm_opr = 0;
		hash_map[i].head->key = 0;
		hash_map[i].head->value = 0;
		hash_map[i].tail->prev = hash_map[i].head;
		hash_map[i].tail->next = NULL;
		hash_map[i].tail->asm_opr = 0;
		hash_map[i].tail->key = 0;
		hash_map[i].tail->value = 0;
		hash_map[i].node_cnt = 0;
	}
}

void	print_hash_map(t_admin *hash_map)
{
	int		i;
	t_node	*cur_node;

	i = -1;
	while(++i <= 52)
	{
		cur_node = hash_map[i].head->next;
		while (cur_node != hash_map[i].tail)
		{
			printf("%s", cur_node->key);
			if (cur_node->value != 0)
				printf("=\"%s\"\n", cur_node->value);
			else
				printf("\n");
			cur_node = cur_node->next;
		}
	}
}
