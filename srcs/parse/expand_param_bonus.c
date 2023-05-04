/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:21:33 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 17:18:04 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse_bonus.h"
#include "libft.h"
#include "safe_function_bonus.h"

static char	*get_search_str(char **p_str)
{
	int		len;
	char	*search_str;

	len = 0;
	while ((*p_str)[len] != 0 && (ft_isalnum((*p_str)[len]) \
	|| (*p_str)[len] == '_'))
		++len;
	search_str = (char *)malloc_s(len + 1);
	search_str[len] = 0;
	len = 0;
	while ((*p_str)[len] != 0 && (ft_isalnum((*p_str)[len]) \
	|| (*p_str)[len] == '_'))
	{
		search_str[len] = (*p_str)[len];
		++len;
	}
	(*p_str) += (len - 1);
	return (search_str);
}

//*p_str is a address right next to $
static char	*get_param_value(t_admin *hash_map, char **p_str)
{
	char	*search_str;
	t_node	*node;

	if (**p_str == '?')
		return (search_node(hash_map, "?")->value);
	search_str = get_search_str(p_str);
	node = search_node(hash_map, search_str);
	free(search_str);
	if (node)
		return (node->value);
	return (0);
}

char	*get_param_expand_empty(t_admin *hash_map, char *str)
{
	size_t	len;
	char	*empty_str;

	len = 0;
	while (*str)
	{
		if (*str != '$')
			++len;
		else if (ft_isalpha(*(str + 1)) || *(str + 1) == '_' \
		|| *(str + 1) == '?')
		{
			++str;
			len += ft_strlen(get_param_value(hash_map, &str));
		}
		else
			++len;
		if (*str)
			++str;
	}
	empty_str = (char *)malloc_s(len + 1);
	empty_str[len] = 0;
	return (empty_str);
}

void	fill_param_expand(t_admin *hash_map, char *str, char *expand)
{
	size_t	len;
	char	*param_value;

	len = 0;
	while (*str)
	{
		if (*str != '$')
			expand[len++] = *str;
		else if (ft_isalpha(*(str + 1)) || *(str + 1) == '_' \
		|| *(str + 1) == '?')
		{
			++str;
			param_value = get_param_value(hash_map, &str);
			if (param_value)
			{
				while (*param_value)
					expand[len++] = *(param_value++);
			}
		}
		else
			expand[len++] = *str;
		if (*str)
			++str;
	}
}

void	expand_param(t_admin *hash_map, t_token_list *tl, t_token *token)
{
	int		paren_depth;
	char	*expand_str;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && (token->type == and || token->type == or))
			break ;
		change_paren_depth(&paren_depth, token);
		if (paren_depth == 0 && token->type == word && \
		is_param_expandable(token->string))
		{
			expand_str = get_param_expand_empty(hash_map, token->string);
			fill_param_expand(hash_map, token->string, expand_str);
			free(token->string);
			token->string = expand_str;
			if (ft_strlen(expand_str) == 0 && token->expand == not_expanded)
				token = delete_certain_token(tl, token);
		}
		if (token == 0)
			token = tl->head;
		else
			token = token->next;
	}
}
