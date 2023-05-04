/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:36:25 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:35 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "safe_function.h"
#include "libft.h"

static int	genral_syntax_err(t_token *token)
{
	write_s(2, "minishell: syntax error near unexpected token `", 47);
	write_s(2, token->string, ft_strlen(token->string));
	write_s(2, "'\n", 2);
	return (1);
}

// last_token means token before end token
static int	readline_syntax_err(int paren_depth, t_syntax_s prev, \
t_token *last_token)
{
	t_state	state;
	char	*str;

	if (prev == start)
		return (0);
	if (paren_depth != 0 || prev == a_bracket || prev == done_a_bracket \
	|| prev == none)
		return (write_s(2, \
		"minishell: syntax error near unexpected token `readline'\n", 57), 1);
	if (last_token->type == word)
	{
		str = last_token->string;
		state = init_state();
		while (*str)
			state = get_tokenize_state(state, str++);
		if (state.num_s == quote)
			return (write_s(2, \
		"minishell: syntax error near unexpected token `readline'\n", 57), 1);
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
