/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:44:04 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:13:56 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parse_bonus.h"
#include "safe_function_bonus.h"

void	init_list(t_token_list **matched_result)
{
	(*matched_result) = (t_token_list *)malloc_s(sizeof(t_token_list));
	(*matched_result)->head = NULL;
	(*matched_result)->tail = NULL;
}

void	free_pattern_list(t_token_list **pattern)
{
	t_token	*del_token;
	t_token	*cur_token;

	cur_token = (*pattern)->head;
	while (cur_token != NULL)
	{
		del_token = cur_token;
		cur_token = cur_token->next;
		free(del_token->string);
		free(del_token);
	}
	free(*pattern);
}

t_token	*get_head_token(t_token_list **matched_result)
{
	t_token	*head_node;

	head_node = (*matched_result)->head;
	free(*matched_result);
	return (head_node);
}

void	config_for_directory(t_token *pattern, char *path, \
int *dir_flag, DIR **dir_pptr)
{
	*dir_pptr = opendir(path);
	if (pattern->next == NULL \
		&& pattern->string[ft_strlen(pattern->string) - 1] == '/')
		*dir_flag = 1;
	else
		*dir_flag = 0;
}

int	is_link_file(char *filename)
{
	if (filename[0] == '.')
		return (1);
	return (0);
}
