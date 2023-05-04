/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_and_pattern.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:24:01 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:14:00 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parse.h"
#include "libft.h"
#include "safe_function.h"

static char	*get_path(char *wild_card_str);
static void	get_pattern(t_token_list *pattern_list, \
int path_len, char *wild_card_str);
static void	init(char **path, int *i, int *add_len, int *path_len);

void	get_path_and_pattern(char *wild_card_str, char **path, \
char **absolute_path, t_token_list *pattern_list)
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
		*absolute_path = ft_strdup_s("");
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
	init(&path, &i, &add_len, &path_len);
	while (wild_card_str[i])
	{
		if (wild_card_str[i] == '*')
			break ;
		if (wild_card_str[i] == '/')
		{
			path = ft_substr_s(wild_card_str, 0, path_len + add_len + 1);
			path_len = ft_strlen(path);
			add_len = 0;
		}
		else
			add_len++;
		i++;
	}
	return (path);
}

static void	get_pattern(t_token_list *pl, \
int path_len, char *wc_str)
{
	int	s_idx;
	int	e_idx;

	s_idx = path_len;
	e_idx = s_idx;
	while (1)
	{
		if (wc_str[e_idx] == '/')
		{
			add_token(pl, ft_substr_s(wc_str, s_idx, e_idx - s_idx + 1));
			s_idx = e_idx + 1;
			if (wc_str[e_idx + 1] == '\0')
			{
				pl->tail->next = NULL;
				break ;
			}
		}
		else if (wc_str[e_idx] == 0)
		{
			add_token(pl, ft_substr_s(wc_str, s_idx, e_idx - s_idx + 1));
			pl->tail->next = NULL;
			break ;
		}
		++e_idx;
	}
}

static void	init(char **path, int *i, int *add_len, int *path_len)
{
	*path = NULL;
	*i = 0;
	*add_len = 0;
	*path_len = 0;
}
