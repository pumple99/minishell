/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:08:15 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/03 20:05:51 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "list.h"

t_token_list	parse_line(char *line)
{
	t_token_list	parsed;

	parsed = tokenize_line(line);
	if (is_syntax_err(parsed))
	{
		while (parsed.head->type != end)
			delete_certain_token(&parsed, parsed.head);
	}
	return (parsed);
}
