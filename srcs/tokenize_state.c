/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:36:36 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/05 19:00:23 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

//prev state is inside, outside, or op_end
static t_state	prev_general(t_state prev_state, char c)
{
	t_state	new;

	new.char_s = c;
	if (c == ' ' || c == '\t')
		return (new.num_s = outside, new);
	else if (c == '&')
		return (new.num_s = ampersand, new);
	else if (c == '|' || c == '<' || c == '>')
		return (new.num_s = op_may_change, new);
	else if (c == '\'' || c == '\"')
		return (new.num_s = quote, new);
	else if (c == '(' || c == ')')
		return (new.num_s = op_end, new);
	else
		return (new.num_s = inside, new);
}

//quote includes double quote
static t_state	prev_is_quote(t_state prev_state, char c)
{
	t_state	new;

	new.char_s = prev_state.char_s;
	if (c != prev_state.char_s)
		return (new.num_s = prev_state.num_s, new);
	else
		return (new.num_s = inside, new);
}

static t_state	prev_is_ampersand(t_state prev_state, char c)
{
	t_state	new;

	new.char_s = c;
	if (c == ' ' || c == '\t')
		return (new.num_s = outside, new);
	else if (c == '|' || c == '<' || c == '>')
		return (new.num_s = op_may_change, new);
	else if (c == '\'' || c == '\"')
		return (new.num_s = quote, new);
	else if (c == '(' || c == ')' || c == '&')
		return (new.num_s = op_end, new);
	else
		return (new.num_s = inside, new);
}

static t_state	prev_is_op_may_change(t_state prev_state, char c)
{
	t_state	new;

	new.char_s = c;
	if (c == ' ' || c == '\t')
		return (new.num_s = outside, new);
	else if (c == '&')
		return (new.num_s = ampersand, new);
	else if (c == '|' || c == '<' || c == '>')
	{
		if (prev_state.char_s == c)
			return (new.num_s = op_end, new);
		else
			return (new.num_s = op_may_change, new);
	}
	else if (c == '\'' || c == '\"')
		return (new.num_s = quote, new);
	else if (c == '(' || c == ')')
		return (new.num_s = op_end, new);
	else
		return (new.num_s = inside, new);
}

t_state	get_new_state(t_state prev_state, char c)
{
	if (prev_state.num_s == outside || prev_state.num_s == op_end)
		return (prev_general(prev_state, c));
	else if (prev_state.num_s == quote)
		return (prev_is_quote(prev_state, c));
	else if (prev_state.num_s == ampersand)
		return (prev_is_ampersand(prev_state, c));
	else if (prev_state.num_s == op_may_change)
		return (prev_is_op_may_change(prev_state, c));
}
