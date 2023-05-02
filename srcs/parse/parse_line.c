/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:08:15 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/02 15:23:25 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "list.h"

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
	return (parsed);
}
