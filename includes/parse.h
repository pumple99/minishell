/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:11:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/01 19:56:27 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <dirent.h>
# include <sys/stat.h>
# include "list.h"

//quote includes double quote
typedef enum e_num_state
{
	outside = 1,
	inside,
	quote,
	op_paren,
	op_may_change,
	op_end = 6
}	t_num_state;

typedef struct s_state
{
	t_num_state	num_s;
	char		char_s;
}	t_state;

typedef enum e_token_type
{
	word = 7,
	paren_l,
	paren_r,
	redirect_r,
	redirect_l,
	append,
	heredoc,
	and,
	or,
	_pipe,
	end = 17
}	t_token_type;

typedef enum e_expand_type
{
	quote_word = 18,
	quote_end,
	non_quote,
	non_quote_end,
	not_expanded,
	wild_card,
	wild_card_end = 24
}	t_expand_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	t_expand_type	expand;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

typedef enum e_syntax_s
{
	start = 25,
	none,
	exist,
	a_bracket,
	done,
	done_a_bracket,
	error = 31
}	t_syntax_s;

typedef struct s_match
{
	int	pattern_len;
	int	string_len;
	int	string_index;
	int	pattern_index;
	int	last_wildcard_idx;
	int	str_backtrack_idx;
	int	next_to_wildcard_idx;
}				t_match;

typedef struct s_recur
{
	DIR				*dir_ptr;
	struct dirent	*filename;
	struct stat		buf;
	char			*path_filename;
	int				dir_flag;
}				t_recur;

//parse_line.c
t_token_list	parse_line(t_admin *hash_map, char *line);

//tl_basic_func.c
t_token			*new_token(char *token_str);
void			add_token(t_token_list *tl, char *token_str);
void			delete_next_token(t_token *prev_token);
t_token			*delete_certain_token(t_token_list *tl, t_token *token);
t_token			*insert_token_to_next(t_token *prev_token, char *str);

//tl_utils
void			delete_residue(t_token *first_token);
t_token			*delete_one_word(t_token_list *tl, t_token *first_token);
t_token			*find_next_word_or_operation(t_token *curr_token);
void			insert_token_list(t_token_list *tl, t_token *prev, \
t_token *first_of_tl);

//tokenize_state.c
t_state			get_tokenize_state(t_state prev_state, char *str);
t_state			init_state(void);

//tokenize_utils.c
int				is_arr_size_plus(t_state prev, t_state new);
int				is_pre_break_condition(t_state prev, t_state new);
t_token_type	get_token_type(char *str);

//tokenize.c
t_token_list	tokenize_line(char *line);

//syntax_state.c
t_syntax_s		get_syntax_state(t_syntax_s prev, int *p_depth, \
t_token_type type);

//syntax_err.c
int				is_syntax_err(t_token_list token_list);

//join_quote_split.c
void			join_quote_split(t_token_list *tl, t_token *token);

//quote_split.c
void			quote_split(t_token_list *tl, t_token *token);

//expand.c
int				is_include_quote(char *str);
int				is_param_expandable(char *str);
void			expand_until_or_and_end(t_admin *hash_map, \
t_token_list *tl, t_token *token);
void			change_paren_depth(int *paren_depth, t_token *token);

//expand_param.c
void			expand_param(t_admin *hash_map, t_token_list *tl, \
t_token *token);

//expand_word_split.c
void			expand_word_split(t_token_list *tl, t_token *token);

//expand_filename.c
void			expand_filename(t_token_list *tl, t_token *token);
void			get_path_and_pattern(char *wild_card_str, char **path, \
char **absolute_path, t_token_list *pattern_list);

//expand_filename_utils.c
void			init_list(t_token_list **matched_result);
void			free_pattern_list(t_token_list **pattern);
t_token			*get_head_token(t_token_list **matched_result);
int				is_link_file(char *filename);
void			config_for_directory(t_token *pattern, char *path, \
									int *dir_flag, DIR **dir_pptr);

//recursive_search_file
void			recur_search(t_token_list *matched_lp, char *path, \
						char *abs_path, t_token *pattern);

//get_wild_card_str.c
int				is_include_wild_card(t_token *first_token);
char			*get_wild_card_str(t_token *first_token);

//is_match.c
int				is_match(char *string, char *pattern);

//sort_matched_list.c
void			sort_matched_result(t_token_list *ml);

#endif
