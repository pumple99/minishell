/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_and_pattern.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:24:01 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 16:00:39 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static char	*get_path(char *wild_card_str);
static void	get_pattern(t_token_list *pattern_list, int path_len, char *wild_card_str);

void	get_path_and_pattern(char *wild_card_str, char **path, char **absolute_path, t_token_list *pattern_list)
{
	int	path_len;

	*path = get_path(wild_card_str);
	if (*path == NULL)
	{
		*path = getcwd_s(NULL, 0);
		*absolute_path = getcwd_s(NULL, 0);
		get_pattern(pattern_list, 0, wild_card_str);
	}
	else
	{
		path_len = ft_strlen(*path);
		if ((*path)[path_len - 1] == '/')
			(*path)[path_len - 1] = '\0';
		*absolute_path = ft_strdup("");
		get_pattern(pattern_list, path_len, wild_card_str);
	}
}

static char	*get_path(char *wild_card_str)
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
			if (wild_card_str[end_idx + 1] == '\0')
			{
				pattern_list->tail->next = NULL;
				break ;
			}
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
