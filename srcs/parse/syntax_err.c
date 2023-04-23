/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:36:25 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 19:15:13 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse_bonus.h"
#include "../../libft/pf_printf.h"

static int	genral_syntax_err(t_token *token)
{
	fd_printf(2, "minishell: syntax error near unexpected token `%s'\n" \
	, token->string);
	return (1);
}

// last_token means token before end token
static int	readline_syntax_err(int paren_depth, t_syntax_s prev, \
t_token *last_token)
{
	t_state	state;
	char	*str;

	if (paren_depth != 0 || prev == a_bracket || prev == done_a_bracket \
	|| prev == none)
		return (fd_printf(2, \
		"minishell: syntax error near unexpected token `%s'\n", "readline"), 1);
	if (last_token->type == word)
	{
		str = last_token->string;
		state = init_state();
		while (*str)
			state = get_tokenize_state(state, str++);
		if (state.num_s == quote)
			return (fd_printf(2, \
		"minishell: syntax error near unexpected token `%s'\n", "readline"), 1);
	}
	return (0);
}

int	is_syntax_err(t_token_list token_list)
{
	int			paren_depth;
	t_syntax_s	prev;
	t_syntax_s	new;
	t_token		*token;
	t_token		*prev_token;

	prev = start;
	paren_depth = 0;
	token = token_list.head;
	while (token->type != end)
	{
		new = get_syntax_state(prev, &paren_depth, token->type);
		if (new == error)
			return (genral_syntax_err(token));
		prev = new;
		prev_token = token;
		token = token->next;
	}
	return (readline_syntax_err(paren_depth, prev, prev_token));
}
