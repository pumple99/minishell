/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:34 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 19:15:06 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse_bonus.h"
#include "../../libft/libft.h"

static t_token	*get_wild_card_expand_list(t_token *token);
static void		change_last_expand_type(t_token *list);

void	expand_filename(t_token_list *tl)
{
	t_token	*token;
	t_token	*wild_card_expand_list;
	t_token	*temp;

	token = tl->head;
	while (token->type != end)
	{
		if (token->type == heredoc)
			token = token->next->next;
		else if (token->type == word && is_include_wild_card(token))
		{
			temp = find_next_word_or_operation(token);
			wild_card_expand_list = get_wild_card_expand_list(token);
			if (wild_card_expand_list)
			{
				change_last_expand_type(wild_card_expand_list);
				insert_token_list(tl, delete_one_word(tl, token), \
				wild_card_expand_list);
			}
			token = temp;
		}
		else
			token = token->next;
	}
}

static void	change_last_expand_type(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr->next)
		curr = curr->next;
	curr->expand = wild_card_end;
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
	recursive_search_file(matched_result, path, absolute_path, \
	pattern_list->head);
	free_pattern_list(&pattern_list);
	return (free(path), free(wild_card_str), \
	free(absolute_path), get_head_token(&matched_result));
}
