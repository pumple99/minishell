/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:34 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/18 15:52:20 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../libft/libft.h"
#include "../../includes/minishell.h"

#include <stdlib.h>
#include <sys/types.h>

static void		init_list(t_token_list **matched_result);
static t_token	*get_wild_card_expand_list(t_token *token);
static void		free_pattern_list(t_token_list **pattern);


void	expand_filename(t_token_list *tl)
{
	t_token	*token;
	t_token	*wild_card_expand_list;
	t_token	*temp;

	token = tl->head;
	while (token->type != end)
	{
		if (token->type == word && is_include_wild_card(token))
		{
			temp = token->next;
			wild_card_expand_list = get_wild_card_expand_list(token);
			if (wild_card_expand_list)
			{
				insert_token_list(tl, delete_one_word(tl, token), \
				wild_card_expand_list);
			}
			token = temp;
		}
		else
			token = token->next;
	}
}

static t_token	*get_wild_card_expand_list(t_token *token)
{
	t_token_list	*matched_result;
	t_token_list	*pattern_list;
	char			*path;
	char			*absolute_path;
	char			*wild_card_str;

	init_list(&matched_result);
	init_list(&pattern_list);
	wild_card_str = get_wild_card_str(token);
	get_path_and_pattern(wild_card_str, &path, &absolute_path, pattern_list);
	recursive_search_file(matched_result, path, absolute_path, pattern_list->head);
	free_pattern_list(&pattern_list);
	t_token	*head = matched_result->head;
	free(matched_result);
	if (matched_result->head == NULL)
		return (free(path), free(wild_card_str), free(absolute_path), head);
	matched_result->tail->next = NULL;
	return (free(path), free(wild_card_str), free(absolute_path), head);
}

static void	init_list(t_token_list **matched_result)
{
	(*matched_result) = (t_token_list *)malloc(sizeof(t_token_list));
	if ((*matched_result) == NULL)
		malloc_error();
	(*matched_result)->head = NULL;
	(*matched_result)->tail = NULL;
}

static void	free_pattern_list(t_token_list **pattern)
{
	t_token	*del_token;
	t_token	*cur_token;

	cur_token = (*pattern)->head;
	while (cur_token != NULL)
	{
		del_token = cur_token;
		cur_token = cur_token->next;
		free(del_token->string);
		free(del_token);
	}
	free(*pattern);
}