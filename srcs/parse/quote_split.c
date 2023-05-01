/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:41:56 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/01 20:38:45 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "safe_function.h"

static int	get_quote_split_len(char *str)
{
	int		len;
	char	first_char;

	first_char = *str;
	if (first_char == '\"' || first_char == '\'')
	{
		len = 1;
		while (str[len] != first_char && str[len] != 0)
			++len;
		++len;
	}
	else
	{
		len = 1;
		while (str[len] != 0 && str[len] != '\'' && str[len] != '\"')
			++len;
	}
	return (len);
}

static char	*get_quote_split_str(char **str)
{
	char	*split_str;
	int		idx;
	int		len;

	len = get_quote_split_len(*str);
	split_str = (char *)malloc_s(len + 1);
	split_str[len] = 0;
	idx = -1;
	while (++idx < len)
	{
		split_str[idx] = **str;
		++(*str);
	}
	return (split_str);
}

static void	allocate_expand_type(t_token *token)
{
	char	*str;

	str = token->string;
	if (*str == '\'' || *str == '\"')
		token->expand = quote_word;
	else
		token->expand = non_quote;
}

static void	quote_split_word(t_token_list *tl, t_token *first_token, char *str)
{
	char	*temp;
	t_token	*temp_token;

	temp_token = first_token;
	while (*str)
	{
		temp = get_quote_split_str(&str);
		temp_token = insert_token_to_next(temp_token, temp);
		allocate_expand_type(temp_token);
	}
	delete_certain_token(tl, first_token);
	if (temp_token->expand == quote_word)
		temp_token->expand = quote_end;
	else
		temp_token->expand = non_quote_end;
}

void	quote_split(t_token_list *tl, t_token *token)
{
	int		paren_depth;
	t_token	*temp;
	char	*str;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && (token->type == and || token->type == or))
			break ;
		change_paren_depth(&paren_depth, token);
		if (paren_depth == 0 && token->expand == not_expanded && \
		token->type == word && is_include_quote(token->string))
		{
			str = token->string;
			temp = token->next;
			quote_split_word(tl, token, str);
			token = temp;
		}
		else
			token = token->next;
	}
}
