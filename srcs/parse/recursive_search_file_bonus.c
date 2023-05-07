/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search_file_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:23:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/07 22:44:11 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h> 
#include "libft.h"
#include "parse_bonus.h"
#include "minishell_bonus.h"
#include "safe_function_bonus.h"

static void		add_list(t_token_list *matched_list_ptr, \
							char *path, char *absolute_path);
static int		get_file_name(DIR *dir_ptr, struct dirent **filename);
static int		get_filename_with_path(char *path, t_recur *v);

void	recur_search(t_token_list *matched_lp, char *path, \
char *abs_path, t_token *pattern)
{
	t_recur	v;

	config_for_directory(pattern, path, &v.dir_flag, &v.dir_ptr);
	while (1)
	{
		if (!get_file_name(v.dir_ptr, &v.filename))
			break ;
		if (!get_filename_with_path(path, &v))
			continue ;
		if (is_match(v.filename->d_name, pattern->string))
		{
			if (S_ISDIR(v.buf.st_mode) && pattern->next == NULL)
				add_list(matched_lp, v.path_filename, abs_path);
			else if (S_ISDIR(v.buf.st_mode))
				recur_search(matched_lp, v.path_filename, \
								abs_path, pattern->next);
			else if (S_ISREG(v.buf.st_mode))
				if (pattern->next == NULL && v.dir_flag == 0)
					add_list(matched_lp, v.path_filename, abs_path);
		}
		free(v.path_filename);
	}
	closedir_s(v.dir_ptr);
}

static void	add_list(t_token_list *matched_list_ptr, \
char *path, char *absolute_path)
{
	int		abs_len;
	char	*add_string;

	abs_len = ft_strlen(absolute_path);
	if (abs_len == 0)
	{
		add_string = ft_substr_s(path, 0, 30000);
		add_token(matched_list_ptr, add_string);
	}
	else
	{
		add_string = ft_substr_s(path, abs_len + 1, 30000);
		add_token(matched_list_ptr, add_string);
	}
	matched_list_ptr->tail->ambi = ambiguous;
}

static int	get_file_name(DIR *dir_ptr, struct dirent **filename)
{
	*filename = readdir_s(dir_ptr);
	if (*filename == NULL)
		return (0);
	return (1);
}

static int	get_filename_with_path(char *path, t_recur *v)
{
	v->path_filename = char_join(path, v->filename->d_name, '/');
	if (stat(v->path_filename, &v->buf) == -1 \
	|| is_link_file(v->filename->d_name))
	{
		free(v->path_filename);
		return (0);
	}
	return (1);
}
