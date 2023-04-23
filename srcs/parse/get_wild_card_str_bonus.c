/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wild_card_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:28:19 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 19:15:09 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse_bonus.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	is_wild_card_in_str(char *str)
{
	while (*str)
	{
		if (*(str++) == '*')
			return (1);
	}
	return (0);
}

int	is_include_wild_card(t_token *first_token)
{
	t_token	*token;

	if (first_token->expand == not_expanded)
		return (is_wild_card_in_str(first_token->string));
	token = first_token;
	while (token->expand != non_quote_end && token->expand != quote_end)
	{
		if (token->expand == non_quote && is_wild_card_in_str(token->string))
			return (1);
		token = token->next;
	}
	if (token->expand == non_quote_end && is_wild_card_in_str(token->string))
		return (1);
	return (0);
}

static size_t	get_wild_card_strlen(t_token *first_token)
{
	t_token	*token;
	size_t	len;

	if (first_token->expand == not_expanded)
		return (ft_strlen(first_token->string));
	len = 0;
	token = first_token;
	while (token->expand != non_quote_end && token->expand != quote_end)
	{
		if (token->expand == non_quote)
			len += ft_strlen(token->string);
		else if (token->expand == quote_word)
			len += (ft_strlen(token->string) - 2);
		token = token->next;
	}
	if (token->expand == non_quote_end)
		len += ft_strlen(token->string);
	else if (token->expand == quote_end)
		len += (ft_strlen(token->string) - 2);
	return (len);
}

static void	copy_wild_card_str(t_token *token, char *wild_card_str, int *idx)
{
	char	*str;

	str = token->string;
	if (token->expand == non_quote || token->expand == non_quote_end)
	{
		while (*str)
			wild_card_str[(*idx)++] = *(str++);
		return ;
	}
	++str;
	while (*(str + 1))
	{
		if (*str == '*')
		{
			wild_card_str[(*idx)++] = -1;
			++str;
		}
		else
			wild_card_str[(*idx)++] = *(str++);
	}
}

char	*get_wild_card_str(t_token *first_token)
{
	t_token	*token;
	char	*wild_card_str;
	size_t	len;
	int		idx;

	if (first_token->expand == not_expanded)
		return (ft_strdup(first_token->string));
	token = first_token;
	len = get_wild_card_strlen(first_token);
	wild_card_str = (char *)malloc_s(len + 1);
	wild_card_str[len] = 0;
	idx = 0;
	while (token->expand != non_quote_end && token->expand != quote_end)
	{
		copy_wild_card_str(token, wild_card_str, &idx);
		token = token->next;
	}
	copy_wild_card_str(token, wild_card_str, &idx);
	return (wild_card_str);
}
