/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:08:27 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 17:12:29 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../libft/libft.h"
#include "../../includes/list.h"

static void	quote_removal(t_token_list *tl)
{
	t_token	*token;
	char	*str;

	token = tl->head;
	while (token->type != end)
	{
		if (token->expand == quote_word || token->expand == quote_end)
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

void	expand_token_list(t_admin *hash_map, t_token_list *tl)
{
	quote_split(tl);
	expand_param(hash_map, tl);
	expand_word_split(tl);
	expand_filename(tl);
	quote_removal(tl);
	join_quote_split(tl);
}
