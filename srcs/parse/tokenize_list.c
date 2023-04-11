/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:13:05 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/11 21:51:01 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parse.h"

t_token_list	make_token_list(void)
{
	t_token_list	tl;

	tl.head = 0;
	tl.tail = 0;
	return tl;
}

t_token	*new_token(char *token_str)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == 0)
	{
		//malloc err here
		return (0);
	}
	new->string = token_str;
	new->type = get_token_type(token_str);
	new->next = 0;
	new->expand = not_expanded;
	return (new);
}

void	add_token(t_token_list *tl, char *token_str)
{
	t_token	*new;

	new = new_token(token_str);
	if (tl->tail == 0)
	{
		tl->head = new;
		tl->tail = new;
	}
	else
	{
		tl->tail->next = new;
		tl->tail = new;
	}
}

t_token	*insert_token_to_next(t_token *prev_token, char *str)
{
	t_token	*new;
	
	new = new_token(str);
	new->next = prev_token->next;
	prev_token->next = new;
	return (new);
}

void	delete_next_token(t_token *prev_token)
{
	t_token	*to_delete;
	t_token	*next_of_to_delete;

	to_delete = prev_token->next;
	next_of_to_delete = to_delete->next;
	prev_token->next = next_of_to_delete;
	free(to_delete->string);
	free(to_delete);
}
