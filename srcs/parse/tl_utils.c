/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:16:16 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/18 21:17:36 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	delete_residue(t_token *first_token)
{
	while (first_token->next->expand != quote_end && \
	first_token->next->expand != non_quote_end)
	{
		delete_next_token(first_token);
	}
	delete_next_token(first_token);
}

// delete one token(expand == not_expanded) or delete sevral token
// until type == word and expand == ~_end
t_token	*delete_one_word(t_token_list *tl, t_token *first_token)
{
	if (first_token->expand == non_quote || first_token->expand == quote_word)
		delete_residue(first_token);
	return (delete_certain_token(tl, first_token));
}

t_token	*find_next_word_or_operation(t_token *curr_token)
{
	t_token	*token;

	if (curr_token->expand == not_expanded)
		return (curr_token->next);
	token = curr_token;
	while (token->expand == non_quote || token->expand == quote_word)
		token = token->next;
	return (token->next);
}

void	insert_token_list(t_token_list *tl, t_token *prev, t_token *first_of_tl)
{
	t_token	*next_of_prev;
	t_token	*temp;

	if (prev == 0)
		next_of_prev = tl->head;
	else
		next_of_prev = prev->next;
	temp = first_of_tl;
	while (temp->next)
		temp = temp->next;
	temp->next = next_of_prev;
	if (prev == 0)
		tl->head = first_of_tl;
	else
		prev->next = first_of_tl;
}