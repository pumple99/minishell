/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_and_pattern.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:24:01 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/16 18:03:58 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	get_path_and_pattern(char *wild_card_str, char **path, char **absolute_path, t_token_list *pattern_list) // path를 할당하고, pattern 리스트를 생성해주는 함수.
{
	*path = get_path(wild_card_str);
	if (*path == NULL)
	{
		*path = getcwd(NULL, 0);
		*absolute_path = ft_strdup("");
		get_pattern(pattern_list, 0, wild_card_str);
	}
	else
	{
		*absolute_path = ft_strdup(*path);
		get_pattern(pattern_list, ft_strlen(*path), wild_card_str);
	}
}

static char	*get_path(char *wild_card_str) // 무조건 별이 들어오는 부분.
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

static void	get_pattern(t_token_list *pattern_list, int path_len, char *wild_card_str)
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
