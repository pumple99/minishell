/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:11:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/14 15:10:30 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "./list.h"

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
	pipe,
	end = 17
}	t_token_type;

typedef	enum e_expand_type
{
	quote_word = 18,
	quote_end,
	non_quote,
	non_quote_end,
	not_expanded = 22
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
	start = 23,
	none,
	exist,
	a_bracket,
	done,
	done_a_bracket,
	error
}	t_syntax_s;

//tokenize_state.c
t_state			get_tokenize_state(t_state prev_state, char *str);
t_state			init_state(void);

//tokenize_utils.c
int				is_arr_size_plus(t_state prev, t_state new);
int				is_pre_break_condition(t_state prev, t_state new);
t_token_type	get_token_type(char *str);

//tokenize_list.c
t_token			*new_token(char *token_str);
void			add_token(t_token_list *tl, char *token_str);
void			delete_next_token(t_token *prev_token);
void			delete_certain_token(t_token_list *tl, t_token *token);
t_token			*insert_token_to_next(t_token *prev_token, char *str);

//tokenize.c
t_token_list	tokenize_line(char *line);

//syntax_state.c
t_syntax_s		get_syntax_state(t_syntax_s prev, int *p_depth, \
t_token_type type);

//syntax_err.c
int				is_syntax_err(t_token_list token_list);

//join_quote_split.c
void			join_quote_split(t_token_list *tl);

//quote_split.c
void			quote_split(t_token_list *tl);

//expand.c
int				is_include_quote(char *str);
int				is_param_expandable(char *str);
void			expand_token_list(t_admin *hash_map, t_token_list *tl);

//expand_param.c
void			expand_param(t_admin *hash_map, t_token_list *tl);

//expand_word_split.c
void			expand_word_split(t_token_list *tl);

#endif