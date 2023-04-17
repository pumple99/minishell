/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:23:14 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/17 18:01:18 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/parse.h"
#include "../../includes/minishell.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 

static int		isMatch(char *string, char *pattern);
static void		adding_to_list(t_token_list *matched_list_ptr, char *path, char *abosolute_path, t_token *pattern);
static void		add_list(t_token_list *matched_list_ptr, char *path, char *absolute_path);
static int		is_link_file(char *filename);

void	recursive_search_file(t_token_list *matched_list_ptr, char *path, char *abosolute_path, t_token *pattern)
{
	DIR				*dir_ptr;
	struct dirent	*filename;
	struct stat		buf;
	char			*path_filename;

	if((dir_ptr = opendir(path)) == NULL)
		return ;
	if (pattern->next == NULL)
		return (adding_to_list(matched_list_ptr, path, abosolute_path, pattern));
	while ((filename = readdir(dir_ptr)))
	{
		path_filename = char_join(path, filename->d_name, '/');
		if (stat(path_filename, &buf) == -1 || is_link_file(filename->d_name))
			continue ;
		if (isMatch(filename->d_name, pattern->string) == 1)
		{
			if (S_ISDIR(buf.st_mode) == 1)
				recursive_search_file(matched_list_ptr, path_filename, abosolute_path, pattern->next);
		}
		free(path_filename);
	}
	closedir(dir_ptr);
}

static void	adding_to_list(t_token_list *matched_list_ptr, char *path, char *abosolute_path, t_token *pattern)
{
	DIR				*dir_ptr;
	struct dirent	*filename;
	struct stat		buf;
	char			*path_filename;
	int				dir_flag;

	dir_flag = 0;
	if (pattern->string[ft_strlen(pattern->string) - 1] == '/')
		dir_flag = 1;
	if((dir_ptr = opendir(path)) == NULL)
		return ;
	while ((filename = readdir(dir_ptr)))
	{
		path_filename = char_join(path, filename->d_name, '/');
		if (stat(path_filename, &buf) == -1 || is_link_file(filename->d_name))
			continue ;
		if (isMatch(filename->d_name, pattern->string) == 1)
		{
			if (S_ISDIR(buf.st_mode) == 1)
				add_list(matched_list_ptr, path_filename, abosolute_path);
			else if (dir_flag == 0 && S_ISREG(buf.st_mode) == 1)
				add_list(matched_list_ptr, path_filename, abosolute_path);
		}
		free(path_filename);
	}
	closedir(dir_ptr);
}

static void	add_list(t_token_list *matched_list_ptr, char *path, char *absolute_path)
{
	int		abs_len;

	abs_len = ft_strlen(absolute_path);
	if (abs_len == 0)
		add_token(matched_list_ptr, ft_substr(path, 0, 300));
	else
		add_token(matched_list_ptr, ft_substr(path, abs_len + 1, 300));
	matched_list_ptr->tail->expand = wild_card;
}

static int isMatch(char *string, char *pattern)
{
	int	i;
	int	pattern_len;
	int	string_len;
	int	string_index = 0; // string_index: 문자열의 현재 위치를 나타내는 변수
	int	pattern_index = 0; // pattern_index: 패턴의 현재 위치를 나타내는 변수
	int	lastWildcardIdx = -1; // lastWildcardIdx: 가장 최근의 wildcard(*)가 나타난 인덱스
	int	sBacktrackIdx = -1; // sBacktrackIdx: wildcard가 나타났을 때, 문자열에서 돌아갈 인덱스
	int	nextToWildcardIdx = -1;// nextToWildcardIdx: wildcard 뒤에 오는 패턴 인덱스를 저장

	pattern_len = ft_strlen(pattern);
	string_len = ft_strlen(string);
	if (pattern[pattern_len - 1] == '/')
		--pattern_len;
	while (string_index < string_len)
	{
		if (pattern_index < pattern_len && pattern[pattern_index] == '*') {
			lastWildcardIdx = pattern_index;
			nextToWildcardIdx = ++pattern_index;
			sBacktrackIdx = string_index;
		}
		else if (pattern_index < pattern_len \
		&& ((pattern[pattern_index] == string[string_index]) \
		|| (pattern[pattern_index] == -1 && string[string_index] == '*')))
		{
			++string_index;
			++pattern_index;
		}
		else if (lastWildcardIdx == -1)
			return 0;
		else
		{
			pattern_index = nextToWildcardIdx;
			string_index = ++sBacktrackIdx;
		}
	}
	i = pattern_index;
	while (i < pattern_len) {
		if (pattern[i] != '*')
			return 0;
		i++;
	}
	return 1;
}

static int is_link_file(char *filename)
{
	if (filename[0] == '.')
		return (1);
	return (0);
}
