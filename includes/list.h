/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:51:38 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 16:58:02 by seunghoy         ###   ########.fr       */
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

// key값
// 대입 연산자 존재 시 기본적으로 ""로 세팅됨.
// 대입연산자의 유무.
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
