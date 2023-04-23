/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:08:15 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/23 19:15:12 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse_bonus.h"
#include "../../includes/list.h"

t_token_list	parse_line(t_admin *hash_map, char *line)
{
	t_token_list	parsed;
	t_token			*token;

	parsed = tokenize_line(line);
	if (is_syntax_err(parsed))
	{
		while (parsed.head->type != end)
			delete_certain_token(&parsed, parsed.head);
	}
	else
	{
		expand_token_list(hash_map, &parsed);
	}
	return (parsed);
}
