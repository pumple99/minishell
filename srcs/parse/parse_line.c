/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:08:15 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/12 17:13:52 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_token_list	parse_line(char *line)
{
	t_token_list	parsed;

	parsed = tokenize_line(line);
	if (is_syntax_err(parsed))
	{
		parsed.head->type = end;
	}
	else
	{
		expand_token_list(parsed);
	}
	return (parsed);
}

#include <stdio.h>
int main()
{
	char	*line = "(ls) && abc\"sdlk$lskc'''\"dddslk  sdk'dkjd$dlk'dk\"\"";
	t_token_list	token_list = parse_line(line);
	t_token *token = token_list.head;
	while (token->type != end)
	{
		printf("type: %u, expand: %u, stirng: %s\n", token->type, token->expand, token->string);
		token = token->next;
	}
	// printf("syntax err: %d\n", is_syntax_err(token_list));
}
