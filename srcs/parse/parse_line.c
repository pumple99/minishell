/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:08:15 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/11 18:02:46 by seunghoy         ###   ########.fr       */
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
	char	*line = "   \t\t\t\n\n";
	t_token_list	token_list = tokenize_line(line);
	t_token *token = token_list.head;
	while (token->type != end)
	{
		printf("%u: %s\n", token->type, token->string);
		token = token->next;
	}
	printf("syntax err: %d\n", is_syntax_err(token_list));
}
