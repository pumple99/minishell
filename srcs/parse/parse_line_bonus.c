/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:08:15 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 17:16:58 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

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
