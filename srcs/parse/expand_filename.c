/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:34 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/14 21:22:37 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parse.h"
// #include "list.h"
// #include "libft.h"
// #include "minishell.h"

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <dirent.h> 

// void	init_admin(t_admin **admin);
// int		isMatch(char *string, char *pattern);

// void	expand_filename(t_token_list *tl)
// {
// 	t_token	*token;
// 	char	**matched_list;

// 	token = tl->head;
// 	while (token->type != end)
// 	{
// 		if ((token->type == non_quote || token->type == non_quote_end) && ft_strchr(token->string, '*') != NULL)
// 		{
// 			//expand(tl);
// 		}
// 		token = token->next;
// 	}
// }

// void	expand(t_token *token)
// {
// 	t_admin	*matched_result; // 매칭되는 애들은 여기에 다 붙어있음.
// 	t_admin	*pattern_list; // 와일드 카드 뒷부분의 패턴들은 다 여기에 붙어있음.
// 	char	*path; // 매칭을 할 패턴들의 경로.
// 	int		path_flag; // 경로의 유무를 확인하는 플래그. => 와일드 카드 앞에 경로 존재 시 matched_result에 노드 추가시 경로도 추가해야함.
// 	char	*wild_card_str; // 와일드 카드가 존재하는 문자열

// 	path_flag = 1;
// 	init_list(&matched_result);
// 	init_list(&pattern_list);
// 	wild_card_str = get_wild_card_str(token); // '*'가 존재하는 문자열 가져온다. (도움 필요)
// 	path = get_path(wild_card_str); // '*' 앞에 경로가 존재한다면, 가져온다. => 리스트에 저장 시 경로도 저장해야 한다.
// 	if (path == NULL)
// 	{
// 		path = getcwd(NULL, 0);
// 		path_flag = 0;
// 		get_pattern(pattern_list, 0, wild_card_str); // "~*~/" || "~*~NULL" 을 한 패턴으로 모두 가져온다.
// 	}
// 	get_pattern(pattern_list, ft_strlen(path), wild_card_str); // "~*~/" || "~*~NULL" 을 한 패턴으로 모두 가져온다.
// 	fill_list(matched_result, path, path_flag, pattern_list->head); // 해당 문자열을 가지고, 재귀함수로 들어간다.
// 	free(path);
// 	free(wild_card_str);
// }

// int isMatch(char *string, char *pattern)
// {
// 	int pattern_len;
// 	int	string_len;
// 	int string_index = 0; // string_index: 문자열의 현재 위치를 나타내는 변수
// 	int pattern_index = 0; // pattern_index: 패턴의 현재 위치를 나타내는 변수
// 	int lastWildcardIdx = -1; // lastWildcardIdx: 가장 최근의 wildcard(*)가 나타난 인덱스
// 	int sBacktrackIdx = -1; // sBacktrackIdx: wildcard가 나타났을 때, 문자열에서 돌아갈 인덱스
// 	int nextToWildcardIdx = -1;// nextToWildcardIdx: wildcard 뒤에 오는 패턴 인덱스를 저장

// 	pattern_len = ft_strlen(pattern);
// 	string_len = ft_strlen(string);
// 	if (pattern[pattern_len - 1] == '/')
// 		--pattern_len;
// 	while (string_index < string_len) { // string이 끝날때까지 진행하는 반복문.
// 		// 현재 패턴 인덱스가 유효하고, 문자가 일치하는 경우
// 		if (pattern_index < pattern_len && pattern[pattern_index] == string[string_index]) {
// 			++string_index;
// 			++pattern_index;
// 		}
// 		else if (pattern_index < pattern_len && pattern[pattern_index] == '*') {
// 			lastWildcardIdx = pattern_index; // 최근 등장한 와일드 카드의 주소를 저장하기.
// 			nextToWildcardIdx = ++pattern_index; // wildcard 뒤에 오는 패턴 인덱스를 저장
// 			sBacktrackIdx = string_index; // wildcard가 나타났을 때, 문자열에서 돌아갈 인덱스
// 		}
// 		else if (lastWildcardIdx == -1) { // 이전에 wildcard가 없는 경우
// 			return 0;
// 		}
// 		else { // 와일드 카드가 나타난 적이 있고, 
// 			pattern_index = nextToWildcardIdx;
// 			string_index = ++sBacktrackIdx;
// 		}
// 	}
// 	for (int i = pattern_index; i < pattern_len; i++) { // 마지막으로 wildcard가 나타난 후, 남은 패턴의 모든 문자열이 '*' 인 경우
// 		if (pattern[i] != '*') return 0;
// 	}
// 	return 1;
// }

// void	init_list(t_admin **matched_result)
// {
// 	(*matched_result) = (t_admin *)malloc(sizeof(t_admin));
// 	if ((*matched_result) == NULL)
// 		malloc_error();
// 	(*matched_result)->head = NULL;
// 	(*matched_result)->tail = NULL;
// 	(*matched_result)->node_cnt = 0;
	
// }

// //0. 첫번째 '*' 앞에 경로가 존재하는 경우

// //1. '*'뒤에 "/ + 다른 문자" 가 존재하는 경우.
// //	1) 해당 폴더의 디렉토리들에 대해서 재귀함수 돌리기. => path에 디렉토리 이름만 strjoin하기.



// void	fill_list(t_admin *matched_list_ptr, char *path, int path_flag, t_token *pattern)
// {
// 	DIR				*dir_ptr;
// 	struct dirent	*filename;
// 	struct stat		buf;
// 	char			*path_filename;

// 	if((dir_ptr = opendir(path)) == NULL) // 해당 디렉토리를 열지 못했을 경우.
// 	{
// 		return ;
// 	}
// 	if (pattern->next == NULL)
// 	{
// 		// add_list(); list에 값들 추가하기.
// 		//2. 마지막 '*'뒤에 '/'가 존재하는 경우
// 		//	1) 현재 디렉토리의 서브 디렉토리들만 맨 뒤에 /달아서 파일 가져오기.
// 		//3. 마지막 '*'에 '*'만 존재하는 경우에는 현재 디렉토리의 모든 파일 가져오기.
// 		return ;
// 	}
// 	while ((filename = readdir(dir_ptr)))
// 	{
// 		path_filename = ft_strjoin(path, filename);
// 		if (stat(path_filename, &buf) == -1)
// 			continue ;
// 		if (isMatch(filename, pattern->string) == 1)
// 		{
// 			if (S_ISDIR(buf.st_mode) == 1)
// 			{
// 				fill_list(matched_list_ptr, path_filename, path_flag, pattern->next);
// 			}
// 		}
// 		free(path_filename);
// 	}
// 	closedir(dir_ptr);
// }

// void	adding_to_list(t_admin *matched_list_ptr, char *path, int path_flag, t_token *pattern)
// {
// 	// 경로 + * 이 들어온 경우 -> 리스트에 추가되는 정보는 경로 + 파일들
// 	// 경로 x + *이 들어온 경우 -> 리스트에 추가되는 정보는 그냥 파일 이름들.
// 	DIR				*dir_ptr;
// 	struct dirent	*filename;
// 	struct stat		buf;
// 	char			*path_filename;
// 	int				dir_flag;

// 	dir_flag = 0;
// 	if (pattern->string[ft_strlen(pattern->string) - 1] == '/')
// 		dir_flag = 1;
// 	if((dir_ptr = opendir(path)) == NULL) // 해당 디렉토리를 열지 못했을 경우.
// 	{
// 		return ;
// 	}
// 	while ((filename = readdir(dir_ptr)))
// 	{
// 		path_filename = ft_strjoin(path, filename);
// 		if (stat(path_filename, &buf) == -1)
// 			continue ;
// 		if (isMatch(filename, pattern->string) == 1)
// 		{
// 			// if (path_flag == 1)
// 			// 
// 			if (S_ISDIR(buf.st_mode) == 1)
// 				// add_list
// 			else if (S_ISREG(buf.st_mode) == 1 && dir_flag != 1)
// 				// add_list
// 		}
// 		free(path_filename);
// 	}
// 	closedir(dir_ptr);
// }