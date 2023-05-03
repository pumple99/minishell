/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:03:45 by sindong-yeo       #+#    #+#             */
/*   Updated: 2023/05/03 20:09:18 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "execute.h"
#include "minishell.h"

void	delete_hash_map(t_admin *hash_map)
{
	int		i;
	t_node	*cur_node;
	t_node	*del_node;

	i = -1;
	while (++i <= 54)
	{
		cur_node = hash_map[i].head->next;
		while (cur_node != hash_map[i].tail)
		{
			del_node = cur_node;
			cur_node = cur_node->next;
			if (del_node)
			{
				if (del_node->key)
					free(del_node->key);
				if (del_node->value)
					free(del_node->value);
				free(del_node);
			}
		}
		free(hash_map[i].head);
		free(hash_map[i].tail);
		hash_map[i].node_cnt = 0;
	}
}

void	delete_new_envp(char ***new_envp_ptr)
{
	free_double_pointer(*new_envp_ptr);
	*new_envp_ptr = NULL;
}

void	is_exec_subshell(t_admin *hash_map, char *argv[], char ***envp)
{
	t_token_list	tl;

	tl = parse_line(argv[1]);
	exit(execute(&tl, hash_map, envp));
}
