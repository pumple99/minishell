/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_basic_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:13:05 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:32 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "safe_function.h"

t_token	*new_token(char *token_str)
{
	t_token	*new;

	new = (t_token *)malloc_s(sizeof(t_token));
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

t_token	*delete_certain_token(t_token_list *tl, t_token *token)
{
	t_token	*prev;

	if (tl->head == token)
	{
		tl->head = token->next;
		free(token->string);
		free(token);
		return (0);
	}
	prev = tl->head;
	while (prev->next)
	{
		if (prev->next == token)
		{
			prev->next = token->next;
			free(token->string);
			free(token);
			return (prev);
		}
		prev = prev->next;
	}
	return (0);
}
