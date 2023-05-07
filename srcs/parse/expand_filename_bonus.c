/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:34 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/07 22:43:09 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse_bonus.h"

static t_token	*get_wild_card_expand_list(t_token *token);
static void		change_last_expand_type(t_token *list);
static t_token	*do_expand_filename(t_token_list *tl, t_token *token);

void	expand_filename(t_token_list *tl, t_token *token)
{
	int		paren_depth;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && (token->type == and || token->type == or))
			break ;
		change_paren_depth(&paren_depth, token);
		if (token->type == heredoc)
			token = token->next->next;
		else if (paren_depth == 0 && token->type == word \
		&& is_include_wild_card(token))
			token = do_expand_filename(tl, token);
		else
			token = token->next;
	}
}

static t_token	*do_expand_filename(t_token_list *tl, t_token *token)
{
	t_token	*temp;
	t_token	*wild_card_expand_list;

	temp = find_next_word_or_operation(token);
	wild_card_expand_list = get_wild_card_expand_list(token);
	if (wild_card_expand_list)
	{
		change_last_expand_type(wild_card_expand_list);
		insert_token_list(tl, delete_one_word(tl, token), \
		wild_card_expand_list);
	}
	return (temp);
}

static void	change_last_expand_type(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr->next)
		curr = curr->next;
	curr->ambi = last_ambi;
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
	recur_search(matched_result, path, absolute_path, \
							pattern_list->head);
	if (matched_result->head != NULL)
		matched_result->tail->next = NULL;
	sort_matched_result(matched_result);
	free_pattern_list(&pattern_list);
	return (free(path), free(wild_card_str), \
	free(absolute_path), get_head_token(&matched_result));
}
