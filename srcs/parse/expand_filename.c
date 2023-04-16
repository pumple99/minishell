/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:34 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/16 20:43:25 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../libft/libft.h"
#include "../../includes/minishell.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 

static t_token	*get_wild_card_expand_list(t_token *token);
static int		isMatch(char *string, char *pattern);
static void		recursive_search_file(t_token_list *matched_list_ptr, char *path, char *abosolute_path, t_token *pattern);
static void		adding_to_list(t_token_list *matched_list_ptr, char *path, char *abosolute_path, t_token *pattern);
static void		add_list(t_token_list *matched_list_ptr, char *path, char *absolute_path);
static void		init_list(t_token_list **matched_result);

void	expand_filename(t_token_list *tl)
{
	t_token	*token;
	t_token	*wild_card_expand_list;

	token = tl->head;
	while (token->type != end)
	{
		if (token->type == word && is_include_wild_card(token))
		{
			wild_card_expand_list = get_wild_card_expand_list(token);
			if (wild_card_expand_list)
			{
				insert_token_list(tl, delete_one_word(tl, token), \
				wild_card_expand_list);
			}
			while (token->expand != not_expanded && \
			token->expand != non_quote_end  && token->expand != quote_end)
				token = token->next;
		}
		token = token->next;
	}
}

static t_token	*get_wild_card_expand_list(t_token *token)
{
	t_token_list	*matched_result;
	t_token_list	*pattern_list;
	char			*path;
	char			*absolute_path;
	char			*wild_card_str;

	init_list(&matched_result);
	init_list(&pattern_list);
	wild_card_str = get_wild_card_str(token);
	get_path_and_pattern(wild_card_str, &path, &absolute_path, pattern_list);
	recursive_search_file(matched_result, path, absolute_path, pattern_list->head);
	if (matched_result->head == NULL)
		return (free(path), free(wild_card_str), free(absolute_path), NULL);
	matched_result->tail->next = NULL;
	return (free(path), free(wild_card_str), free(absolute_path), matched_result->head);
}

static void	recursive_search_file(t_token_list *matched_list_ptr, char *path, char *abosolute_path, t_token *pattern)
{
	DIR				*dir_ptr;
	struct dirent	*filename;
	struct stat		buf;
	char			*path_filename;

	char			*prev_path_filename;

	if((dir_ptr = opendir(path)) == NULL)
	{
		return ;
	}
	if (pattern->next == NULL)
	{
		adding_to_list(matched_list_ptr, path, abosolute_path, pattern);
		return ;
	}
	while ((filename = readdir(dir_ptr)))
	{
		path_filename = ft_strjoin(path, "/");
		prev_path_filename = path_filename;
		path_filename = ft_strjoin(path_filename, filename->d_name);
		free(prev_path_filename);
		if (stat(path_filename, &buf) == -1)
			continue ;
		if (isMatch(filename->d_name, pattern->string) == 1)
		{
			if (S_ISDIR(buf.st_mode) == 1)
			{
				recursive_search_file(matched_list_ptr, path_filename, abosolute_path, pattern->next);
			}
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
	t_token			*token;

	char			*prev_path_filename;

	dir_flag = 0;
	if (pattern->string[ft_strlen(pattern->string) - 1] == '/')
		dir_flag = 1;
	if((dir_ptr = opendir(path)) == NULL)
	{
		return ;
	}
	while ((filename = readdir(dir_ptr)))
	{
		path_filename = ft_strjoin(path, "/");
		prev_path_filename = path_filename;
		path_filename = ft_strjoin(path_filename, filename->d_name);
		free(prev_path_filename);
		if (stat(path_filename, &buf) == -1)
			continue ;
		if (isMatch(filename->d_name, pattern->string) == 1)
		{
			if (S_ISDIR(buf.st_mode) == 1)
				add_list(matched_list_ptr, path_filename, abosolute_path);
			else if (S_ISREG(buf.st_mode) == 1 && dir_flag != 1)
				add_list(matched_list_ptr, path_filename, abosolute_path);
		}
		free(path_filename);
	}
	closedir(dir_ptr);
}

static void	add_list(t_token_list *matched_list_ptr, char *path, char *absolute_path)
{
	t_token	*token;

	add_token(matched_list_ptr, ft_strjoin(absolute_path, path));
	matched_list_ptr->tail->expand = wild_card;
}

static void	init_list(t_token_list **matched_result)
{
	(*matched_result) = (t_token_list *)malloc(sizeof(t_token_list));
	if ((*matched_result) == NULL)
		malloc_error();
	(*matched_result)->head = NULL;
	(*matched_result)->tail = NULL;
}

static int isMatch(char *string, char *pattern)
{
	int pattern_len;
	int	string_len;
	int string_index = 0; // string_index: 문자열의 현재 위치를 나타내는 변수
	int pattern_index = 0; // pattern_index: 패턴의 현재 위치를 나타내는 변수
	int lastWildcardIdx = -1; // lastWildcardIdx: 가장 최근의 wildcard(*)가 나타난 인덱스
	int sBacktrackIdx = -1; // sBacktrackIdx: wildcard가 나타났을 때, 문자열에서 돌아갈 인덱스
	int nextToWildcardIdx = -1;// nextToWildcardIdx: wildcard 뒤에 오는 패턴 인덱스를 저장

	pattern_len = ft_strlen(pattern);
	string_len = ft_strlen(string);
	if (pattern[pattern_len - 1] == '/')
		--pattern_len;
	while (string_index < string_len) { // string이 끝날때까지 진행하는 반복문.
		// 현재 패턴 인덱스가 유효하고, 문자가 일치하는 경우
		if (pattern_index < pattern_len && pattern[pattern_index] == string[string_index]) {
			++string_index;
			++pattern_index;
		}
		else if (pattern_index < pattern_len && pattern[pattern_index] == '*') {
			lastWildcardIdx = pattern_index; // 최근 등장한 와일드 카드의 주소를 저장하기.
			nextToWildcardIdx = ++pattern_index; // wildcard 뒤에 오는 패턴 인덱스를 저장
			sBacktrackIdx = string_index; // wildcard가 나타났을 때, 문자열에서 돌아갈 인덱스
		}
		else if (lastWildcardIdx == -1) { // 이전에 wildcard가 없는 경우
			return 0;
		}
		else { // 와일드 카드가 나타난 적이 있고, 
			pattern_index = nextToWildcardIdx;
			string_index = ++sBacktrackIdx;
		}
	}
	for (int i = pattern_index; i < pattern_len; i++) { // 마지막으로 wildcard가 나타난 후, 남은 패턴의 모든 문자열이 '*' 인 경우
		if (pattern[i] != '*') return 0;
	}
	return 1;
}
