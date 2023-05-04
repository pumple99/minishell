/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:31:57 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:17:05 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "safe_function.h"

static int	need_split(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '\n')
			return (1);
		++str;
	}
	return (0);
}

static char	*get_word_split_str(char **str)
{
	char	*split_str;
	int		idx;
	int		len;

	len = 0;
	while ((*str)[len] != 0 && (*str)[len] != ' ' && (*str)[len] != '\t' \
	&& (*str)[len] != '\n')
		++len;
	split_str = (char *)malloc_s(len + 1);
	split_str[len] = 0;
	idx = -1;
	while (++idx < len)
		split_str[idx] = *((*str)++);
	while (**str != 0 && (**str == ' ' || **str == '\t' || **str == '\n'))
		++(*str);
	return (split_str);
}

static void	word_split_one_word(t_token_list *tl, \
t_token *first_token, char *str)
{
	char	*temp;
	t_token	*temp_token;

	while (*str != 0 && (*str == ' ' || *str == '\t' || *str == '\n'))
		++str;
	temp_token = first_token;
	while (*str)
	{
		temp = get_word_split_str(&str);
		temp_token = insert_token_to_next(temp_token, temp);
		temp_token->expand = non_quote_end;
	}
	temp_token->expand = first_token->expand;
	delete_certain_token(tl, first_token);
}

void	expand_word_split(t_token_list *tl, t_token *token)
{
	int		paren_depth;
	t_token	*next;
	char	*str;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && (token->type == and || token->type == or))
			break ;
		change_paren_depth(&paren_depth, token);
		if (paren_depth == 0 && token->type == word \
		&& token->expand != quote_word \
		&& token->expand != quote_end && need_split(token->string))
		{
			str = token->string;
			next = token->next;
			word_split_one_word(tl, token, str);
			token = next;
		}
		else
			token = token->next;
	}
}
