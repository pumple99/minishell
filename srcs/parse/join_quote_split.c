/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quote_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:55:54 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/03 20:04:37 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "libft.h"
#include "safe_function.h"

static char	*get_empty_str(t_token *first_token)
{
	size_t	total;
	t_token	*temp;
	char	*empty_str;

	total = 0;
	temp = first_token;
	while (temp->type != end)
	{
		total += ft_strlen(temp->string);
		if (temp->expand == quote_end || temp->expand == non_quote_end)
			break ;
		temp = temp->next;
	}
	empty_str = (char *)malloc_s(total + 1);
	empty_str[total] = 0;
	return (empty_str);
}

static void	fill_empty_str(t_token *first_token, char *empty_str)
{
	t_token	*temp;
	char	*str;
	int		idx;

	idx = 0;
	temp = first_token;
	while (temp->type != end)
	{
		str = temp->string;
		while (*str)
			empty_str[idx++] = *(str++);
		if (temp->expand == quote_end || temp->expand == non_quote_end)
			break ;
		temp = temp->next;
	}
}

void	join_quote_split(t_token *token)
{
	int		paren_depth;
	char	*joined_word;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && (token->type == and || token->type == or))
			break ;
		change_paren_depth(&paren_depth, token);
		if (paren_depth == 0 \
		&& (token->expand == non_quote || token->expand == quote_word))
		{
			joined_word = get_empty_str(token);
			fill_empty_str(token, joined_word);
			delete_residue(token);
			free(token->string);
			token->string = joined_word;
			token->expand = not_expanded;
		}
		else
			token->expand = not_expanded;
		token = token->next;
	}
}
