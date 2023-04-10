/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:13:05 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/10 20:40:00 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include <stdlib.h>

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
