/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:24:01 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/14 21:42:51 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>

// static void	make_path(char **path, char *wild_card_str, int path_len, int add_len);

// char	*get_path(char *wild_card_str)
// {
// 	int		i;
// 	int		path_len;
// 	int		add_len;
// 	char	*path;

// 	if (wild_card_str[0] != '/')
// 		return (NULL);
// 	path = NULL;
// 	i = -1;
// 	add_len = 0;
// 	path_len = 0;
// 	while (wild_card_str[++i])
// 	{
// 		if (wild_card_str[i] == '*')
// 			break ;
// 		if (wild_card_str[i] == '/')
// 		{
// 			path = ft_substr(wild_card_str, 0, path_len + add_len + 1);
// 			path_len = ft_strlen(path);
// 			add_len = 0;
// 			i++;
// 		}
// 		++add_len;
// 	}
// 	return (path);
// }

// void	get_pattern(/*t_admin *pattern_list, */int path_len, char *wild_card_str)
// {
// 	int	start_idx;
// 	int	end_idx;

// 	start_idx = path_len;
// 	end_idx = start_idx;
// 	while (1)
// 	{
// 		if (wild_card_str[end_idx] == '/')
// 		{
// 			printf("%s\n", ft_substr(wild_card_str, start_idx, end_idx - start_idx + 1));
// 			start_idx = end_idx + 1;
// 		}
// 		else if (wild_card_str[end_idx] == 0)
// 		{
// 			printf("%s\n", ft_substr(wild_card_str, start_idx, end_idx - start_idx + 1));
// 			break ;
// 		}
// 		++end_idx;
// 	}
// }
// // static void	make_path(char **path, char *wild_card_str, int path_len, int add_len)
// // {
// // 	if (*path == NULL)
// // 	{
// // 		*path = (char *)malloc(sizeof(char) * 2);
// // 		if (*path == NULL)
// // 			malloc_error();
// // 		(*path)[0] = '/';
// // 		(*path)[1] = '\0';
// // 	}
// // 	else
// // 	{
// // 		free(*path);
// // 		*path = (char *)malloc(sizeof(char) * (path_len + add_len + 1));
// // 		if (*path == NULL)
// // 			malloc_error();
// // 		ft_strlcpy((*path), wild_card_str, path_len + add_len + 1);
// // 	}
// // }

// int main(void)
// {
// 	char	*str = "/AAA/BBB/CCC/*/E*/F";
// 	char	*path = get_path(str);

// 	printf("%s\n", path);
// 	get_pattern(ft_strlen(path), str);
// 	return (0);
// }