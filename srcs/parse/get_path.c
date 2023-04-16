/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:24:01 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/16 17:43:06 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	make_path(char **path, char *wild_card_str, int path_len, int add_len);

char	*get_path(char *wild_card_str) // 무조건 별이 들어오는 부분.
{
	int		i;
	int		path_len;
	int		add_len;
	char	*path;

	if (wild_card_str[0] != '/')
		return (NULL);
	path = NULL;
	i = 0;
	add_len = 0;
	path_len = 0;
	while (wild_card_str[i])
	{
		if (wild_card_str[i] == '*')
			break ;
		if (wild_card_str[i] == '/')
		{
			path = ft_substr(wild_card_str, 0, path_len + add_len + 1);
			path_len = ft_strlen(path);
			add_len = 0;
		}
		else
			add_len++;
		i++;
	}
	return (path);
}

void	get_pattern(t_token_list *pattern_list, int path_len, char *wild_card_str)
{
	int	start_idx;
	int	end_idx;

	start_idx = path_len;
	end_idx = start_idx;
	while (1)
	{
		if (wild_card_str[end_idx] == '/')
		{
			add_token(pattern_list, ft_substr(wild_card_str, start_idx, end_idx - start_idx + 1));
			start_idx = end_idx + 1;
		}
		else if (wild_card_str[end_idx] == 0)
		{
			add_token(pattern_list, ft_substr(wild_card_str, start_idx, end_idx - start_idx + 1));
			pattern_list->tail->next = NULL;
			break ;
		}
		++end_idx;
	}
}

int main(void)
{
	char	*str = "/AAA/BB/***/*D/*/**";
	char	*path = get_path(str);
	t_token_list	*pattern;

	printf("%s\n", path);
	get_pattern(pattern, ft_strlen(path), str);
	t_token *head = pattern->head;
	while (head != NULL) {
		printf("%s\n", head->string);
	}
	return (0);
}