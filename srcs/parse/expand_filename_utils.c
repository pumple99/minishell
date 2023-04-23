/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:44:04 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/24 00:00:32 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "safe_function.h"

void	init_list(t_token_list **matched_result)
{
	(*matched_result) = (t_token_list *)malloc_s(sizeof(t_token_list));
	(*matched_result)->head = NULL;
	(*matched_result)->tail = NULL;
}

void	free_pattern_list(t_token_list **pattern)
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

t_token	*get_head_token(t_token_list **matched_result)
{
	t_token	*head_node;

	if ((*matched_result)->head != NULL)
		(*matched_result)->tail->next = NULL;
	head_node = (*matched_result)->head;
	free(*matched_result);
	return (head_node);
}
