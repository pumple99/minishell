/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:29 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/07 17:24:16 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parse.h"

static t_token	*make_arr(char *line)
{
	t_state	state;
	t_state	new_state;
	int		token_count;
	t_token	*token_arr;

	state = init_state();
	token_count = 0;
	while (*line)
	{
		new_state = get_new_state(state, line++);
		if (is_arr_size_plus(state, new_state))
			++token_count;
		state = new_state;
	}
	token_arr = (t_token *)malloc(sizeof(t_token) * (token_count + 1));
	if (token_arr)
		token_arr[token_count].type = end;
	return (token_arr);
}

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
		new_state = get_new_state(state, src++);
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
		new_state = get_new_state(state, src);
		if (is_pre_break_condition(state, new_state))
			break ;
		copy_token[str_idx++] = *(src++);
		if (new_state.num_s == op_end || new_state.num_s == op_paren)
			break;
		state = new_state;
	}
	return (copy_token);
}

t_token	*parse_line(char *line)
{
	t_token	*token_arr;
	t_state	state;
	t_state	new_state;
	int		arr_idx;

	token_arr = make_arr(line);
	if (token_arr == 0)
		return (0);
	state = init_state();
	arr_idx = 0;
	while (*line)
	{
		new_state = get_new_state(state, line);
		if (is_arr_size_plus(state, new_state))
		{
			token_arr[arr_idx].string = copy_token_in_line(line);
			if (token_arr[arr_idx].string == 0)
				return (free_parse_arr(token_arr, arr_idx));
			allocate_token_type(token_arr, arr_idx++);
		}
		state = new_state;
		++line;
	}
	return (token_arr);
}

#include <stdio.h>
int main()
{
	char	*line = "ls && (|| ls ) || ls";
	t_token	*token_arr = parse_line(line);
	t_token *temp = token_arr;
	while (token_arr->type != end)
	{
		printf("%u: %s\n", token_arr->type, token_arr->string);
		++token_arr;
	}
	printf("syntax err: %d\n", is_syntax_err(temp));
}
