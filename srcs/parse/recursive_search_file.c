/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:23:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 16:24:34 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/parse.h"
#include "../../includes/minishell.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 

static void		add_list(t_token_list *matched_list_ptr, char *path, char *absolute_path);
static int		is_link_file(char *filename);
static void		config_for_directory(t_token *pattern, char *path, int *dir_flag, DIR **dir_pptr);


void	recursive_search_file(t_token_list *matched_list_ptr, char *path, char *abosolute_path, t_token *pattern)
{
	DIR				*dir_ptr;
	struct dirent	*filename;
	struct stat		buf;
	char			*path_filename;
	int				dir_flag;

	config_for_directory(pattern, path, &dir_flag, &dir_ptr);
	while ((filename = readdir_s(dir_ptr)))
	{
		path_filename = char_join(path, filename->d_name, '/');
		if (path_filename == NULL)
			malloc_error();
		if (stat(path_filename, &buf) == -1 || is_link_file(filename->d_name))
		{
			free(path_filename);
			continue ;
		}
		if (is_match(filename->d_name, pattern->string))
		{
			if (S_ISDIR(buf.st_mode))
			{
				if (pattern->next == NULL)
					add_list(matched_list_ptr, path_filename, abosolute_path);
				else
					recursive_search_file(matched_list_ptr, path_filename, abosolute_path, pattern->next);
			}
			else if (S_ISREG(buf.st_mode))
				if (pattern->next == NULL && dir_flag == 0)
					add_list(matched_list_ptr, path_filename, abosolute_path);
		}
		free(path_filename);
	}
	closedir_s(dir_ptr);
}

static void	add_list(t_token_list *matched_list_ptr, char *path, char *absolute_path)
{
	int		abs_len;
	char	*add_string;

	abs_len = ft_strlen(absolute_path);
	if (abs_len == 0)
	{
		add_string = ft_substr(path, 0, 300);
		if (add_string == NULL)
			malloc_error();
		add_token(matched_list_ptr, add_string);
	}
	else
	{
		add_string = ft_substr(path, abs_len + 1, 300);
		if (add_string == NULL)
			malloc_error();
		add_token(matched_list_ptr, add_string);
	}
	matched_list_ptr->tail->expand = wild_card;
}

static int is_link_file(char *filename)
{
	if (filename[0] == '.')
		return (1);
	return (0);
}

static void	config_for_directory(t_token *pattern, char *path, int *dir_flag, DIR **dir_pptr)
{
	*dir_pptr = opendir(path);
	// if(*dir_pptr == NULL) // 오류나면 어떻게 처리하지?
		// return (-1);
	if (pattern->next == NULL && pattern->string[ft_strlen(pattern->string) - 1] == '/')
		*dir_flag = 1;
	else
		*dir_flag = 0;
}
