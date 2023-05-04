/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:51:38 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:54 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_node	t_node;

typedef struct s_admin
{
	t_node	*head;
	t_node	*tail;
	int		node_cnt;
}						t_admin;

struct	s_node
{
	t_node	*prev;
	char	*key;
	char	*value;
	int		asm_opr;
	t_node	*next;
};

t_node	*create_node(char *export_arg);
void	add_node(t_admin	*hash_map, char *new_arg);
t_node	*search_node(t_admin *hash_map, char *key);
void	delete_node(t_admin *hash_map, char *key, int *re_build_flag);

//utils.c
int		get_index(char *str);

#endif
