/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:23:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/24 19:56:14 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 
#include "libft.h"
#include "parse.h"
#include "minishell.h"
#include "safe_function.h"

static void		add_list(t_token_list *matched_list_ptr, \
							char *path, char *absolute_path);
static int		get_file_name(DIR *dir_ptr, struct dirent **filename);
static int		get_filename_with_path(const char *path, \
										struct dirent *filename, \
										struct stat buf, char **path_filename);

void	recur_search(t_token_list *matched_lp, char *path, \
						char *abs_path, t_token *pattern)
{
	t_recur	v;

	config_for_directory(pattern, path, &v.dir_flag, &v.dir_ptr);
	while (1)
	{
		if (!get_file_name(v.dir_ptr, &v.filename))
			break ;
		if (!get_filename_with_path(path, v.filename, v.buf, &v.path_filename))
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
	matched_list_ptr->tail->expand = wild_card;
}

static int	get_file_name(DIR *dir_ptr, struct dirent **filename)
{
	*filename = readdir_s(dir_ptr);
	if (*filename == NULL)
		return (0);
	return (1);
}

static int	get_filename_with_path(const char *path, struct dirent *filename, \
									struct stat buf, char **path_filename)
{
	*path_filename = char_join(path, filename->d_name, '/');
	if (stat(*path_filename, &buf) == -1 || is_link_file(filename->d_name))
	{
		free(*path_filename);
		return (0);
	}
	return (1);
}
