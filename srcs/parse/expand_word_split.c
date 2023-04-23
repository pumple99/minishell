/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:31:57 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 19:15:07 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parse_bonus.h"
#include "../../libft/libft.h"

static int	is_include_delimiter(char *str)
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

void	expand_word_split(t_token_list *tl)
{
	t_token	*token;
	char	*str;

	token = tl->head;
	while (token->type != end)
	{
		if (token->type == word && token->expand != quote_word \
		&& token->expand != quote_end && is_include_delimiter(token->string))
		{
			str = token->string;
			word_split_one_word(tl, token, str);
		}
		token = token->next;
	}
}
