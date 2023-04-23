/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:36:25 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 19:15:14 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse_bonus.h"

static t_syntax_s	prev_is_none(int *p_depth, t_token_type type)
{
	if (type == paren_r || type == and || type == or || type == _pipe)
		return (error);
	else if (type == word)
		return (exist);
	else if (type == paren_l)
	{
		++(*p_depth);
		return (none);
	}
	else
		return (a_bracket);
}

static t_syntax_s	prev_is_exist(int *p_depth, t_token_type type)
{
	if (type == word)
		return (exist);
	else if (type == paren_l)
		return (error);
	else if (type == and || type == or || type == _pipe)
		return (none);
	else if (type == paren_r)
	{
		if (*p_depth > 0)
		{
			--(*p_depth);
			return (done);
		}
		else
			return (error);
	}
	else
		return (a_bracket);
}

static t_syntax_s	prev_is_done(int *p_depth, t_token_type type)
{
	if (type == paren_l || type == word)
		return (error);
	else if (type == and || type == or || type == _pipe)
		return (none);
	else if (type == paren_r)
	{
		if (*p_depth > 0)
		{
			--(*p_depth);
			return (done);
		}
		else
			return (error);
	}
	else
		return (done_a_bracket);
}

t_syntax_s	get_syntax_state(t_syntax_s prev, int *p_depth, \
t_token_type type)
{
	if (prev == none || prev == start)
		return (prev_is_none(p_depth, type));
	else if (prev == exist)
		return (prev_is_exist(p_depth, type));
	else if (prev == done)
		return (prev_is_done(p_depth, type));
	else if (prev == a_bracket)
	{
		if (type == word)
			return (exist);
		else
			return (error);
	}
	else
	{
		if (type == word)
			return (done);
		else
			return (error);
	}
}
