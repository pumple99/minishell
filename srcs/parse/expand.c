/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:08:27 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/02 16:56:53 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "list.h"

static void	quote_removal(t_token_list *tl, t_token *token)
{
	int		paren_depth;
	char	*str;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && (token->type == and || token->type == or))
			break ;
		change_paren_depth(&paren_depth, token);
		if (paren_depth == 0 \
		&& (token->expand == quote_word || token->expand == quote_end))
		{
			str = token->string;
			while (*(str++))
				*(str - 1) = *str;
			*(str - 3) = 0;
		}
		token = token->next;
	}
}

int	is_include_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (1);
		++str;
	}
	return (0);
}

int	is_param_expandable(char *str)
{
	char	c;

	if (*str == '\'')
		return (0);
	while (*str)
	{
		if (*str == '$')
		{
			c = *(str + 1);
			if (ft_isalpha(c) || c == '_' || c == '?')
				return (1);
		}
		++str;
	}
	return (0);
}

void	change_paren_depth(int *paren_depth, t_token *token)
{
	if (token->type == paren_l)
		++(*paren_depth);
	else if (token->type == paren_r)
		--(*paren_depth);
}

void	expand_until_or_and_end(t_admin *hash_map, \
t_token_list *tl, t_token *token)
{
	if (token == 0)
	{
		quote_split(tl, tl->head);
		expand_param(hash_map, tl, tl->head);
		expand_word_split(tl, tl->head);
		expand_filename(tl, tl->head);
		quote_removal(tl, tl->head);
		join_quote_split(tl, tl->head);
		return ;
	}
	quote_split(tl, token->next);
	expand_param(hash_map, tl, token->next);
	expand_word_split(tl, token->next);
	expand_filename(tl, token->next);
	quote_removal(tl, token->next);
	join_quote_split(tl, token->next);
}
