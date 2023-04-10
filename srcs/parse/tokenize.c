/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:29 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/10 20:58:11 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parse.h"

/*src: word's starting address, not a start of total input
return: size of string, not include " and '*/
static int	get_token_size(char *src)
{
	int		token_size;
	t_state	new_state;
	t_state	state;

	state = init_state();
	token_size = 0;
	while (*src)
	{
		new_state = get_tokenize_state(state, src++);
		if (is_pre_break_condition(state, new_state))
			break ;
		++token_size;
		if (new_state.num_s == op_end || new_state.num_s == op_paren)
			break;
		state = new_state;
	}
	return (token_size);
}

/*src: word's starting address, not a start of total input
return: copied string */
static char	*copy_token_in_line(char *src)
{
	t_state	state;
	t_state	new_state;
	int		token_size;
	int		str_idx;
	char	*copy_token;

	state = init_state();
	str_idx = 0;
	token_size = get_token_size(src);
	copy_token = (char *)malloc(token_size + 1);
	if (copy_token == 0)
		return (0);
	copy_token[token_size] = '\0';
	while (*src)
	{
		new_state = get_tokenize_state(state, src);
		if (is_pre_break_condition(state, new_state))
			break ;
		copy_token[str_idx++] = *(src++);
		if (new_state.num_s == op_end || new_state.num_s == op_paren)
			break;
		state = new_state;
	}
	return (copy_token);
}

t_token_list	tokenize_line(char *line)
{
	t_token_list	token_list;
	t_state			state;
	t_state			new_state;

	token_list = make_token_list();
	state = init_state();
	while (*line)
	{
		new_state = get_tokenize_state(state, line);
		if (is_arr_size_plus(state, new_state))
		{
			add_token(&token_list, copy_token_in_line(line));
		}
		state = new_state;
		++line;
	}
	add_token(&token_list, "end");
	token_list.tail->type = end;
	return (token_list);
}

#include <stdio.h>
int main()
{
	char	*line = "(ls||ls|) && cmd";
	t_token_list	token_list = tokenize_line(line);
	t_token *node = token_list.head;
	while (node->type != end)
	{
		printf("%u: %s\n", node->type, node->string);
		node = node->next;
	}
	printf("syntax err: %d\n", is_syntax_err(token_list));
}
