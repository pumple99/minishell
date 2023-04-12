/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_hash_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:51:01 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 18:19:14 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	init_hash_map(t_admin *hash_map);

void	make_hash_map(t_admin *hash_map, char *envp[], char ***new_envp)
{
	int	i;

	init_hash_map(hash_map);
	i = -1;
	while (envp[++i])
		add_node(hash_map, envp[i]);
	make_new_envp(hash_map, new_envp);
}

static void	init_hash_map(t_admin *hash_map)
{
	int	i;
	
	i = -1;
	while (++i <= 52)
	{
		hash_map[i].head = (t_node *)malloc(sizeof(t_node));
		if (hash_map[i].head == NULL)
			malloc_error();
		hash_map[i].tail = (t_node *)malloc(sizeof(t_node));
		if (hash_map[i].tail == NULL)
			malloc_error();
		hash_map[i].head->next = hash_map[i].tail;
		hash_map[i].head->prev = NULL;
		hash_map[i].tail->prev = hash_map[i].head;
		hash_map[i].tail->next = NULL;
		hash_map[i].node_cnt = 0;
	}
}
