/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:36:36 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/16 17:12:57 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

//prev state is inside, outside, op_paren, or op_end
static t_state	prev_general(t_state prev_state, char *str)
{
	t_state	new;
	char	c;

	c = *str;
	new.char_s = c;
	if (c == ' ' || c == '\t')
		return (new.num_s = outside, new);
	else if (c == '&' && *(str + 1) == '&')
		return (new.num_s = op_may_change, new);
	else if (c == '|' || c == '<' || c == '>')
		return (new.num_s = op_may_change, new);
	else if (c == '\'' || c == '\"')
		return (new.num_s = quote, new);
	else if (c == '(' || c == ')')
		return (new.num_s = op_paren, new);
	else
		return (new.num_s = inside, new);
}

//quote includes double quote
static t_state	prev_is_quote(t_state prev_state, char *str)
{
	t_state	new;

	new.char_s = prev_state.char_s;
	if (*str != prev_state.char_s)
		return (new.num_s = prev_state.num_s, new);
	else
		return (new.num_s = inside, new);
}

static t_state	prev_is_op_may_change(t_state prev_state, char *str)
{
	t_state	new;
	char	c;

	c = *str;
	new.char_s = c;
	if (c == ' ' || c == '\t')
		return (new.num_s = outside, new);
	else if (c == '|' || c == '<' || c == '>' || c == '&')
	{
		if (prev_state.char_s == c)
			return (new.num_s = op_end, new);
		else
			return (new.num_s = op_may_change, new);
	}
	else if (c == '\'' || c == '\"')
		return (new.num_s = quote, new);
	else if (c == '(' || c == ')')
		return (new.num_s = op_paren, new);
	else
		return (new.num_s = inside, new);
}

// else condition is same with condition below
// if (prev_state.num_s == outside || prev_state.num_s == op_end \
// 	|| prev_state.num_s == op_paren || prev_state.num_s == inside)
// 		return (prev_general(prev_state, str));
t_state	get_tokenize_state(t_state prev_state, char *str)
{
	if (prev_state.num_s == quote)
		return (prev_is_quote(prev_state, str));
	else if (prev_state.num_s == op_may_change)
		return (prev_is_op_may_change(prev_state, str));
	else
		return (prev_general(prev_state, str));
}

t_state	init_state(void)
{
	t_state	new;

	new.char_s = 0;
	new.num_s = outside;
	return (new);
}
