#ifndef LIST_H
# define LIST_H

typedef struct	s_node	t_node;

typedef struct	s_admin
{
	t_node	*head;
	t_node	*tail;
	int		node_cnt;
}				t_admin;

struct	s_node
{
	t_node	*prev;
	char	*key;		// key값
	char	*value;		// 대입 연산자 존재 시 기본적으로 ""로 세팅됨.
	int		asm_opr;	// 대입연산자의 유무.
	t_node	*next;
};

t_node	*create_node(char *export_arg);
void	add_node(t_admin	*hash_map, char *new_arg);

#endif
