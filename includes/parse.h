/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:11:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/10 20:49:25 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

//quote includes double quote
typedef enum e_num_state
{
	outside = 1,
	inside,
	quote,
	op_paren,
	op_may_change,
	op_end
}	t_num_state;

typedef struct s_state
{
	t_num_state	num_s;
	char		char_s;
}	t_state;

typedef enum e_token_type
{
	word = 10,
	paren_l,
	paren_r,
	redirect_r,
	redirect_l,
	append,
	heredoc,
	and,
	or,
	pipe,
	end
}	t_token_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

typedef enum e_syntax_s
{
	none = 20,
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
t_token			*free_parse_arr(t_token *token_arr, int arr_idx);

//tokenize_list.c
t_token_list	make_token_list(void);
t_token			*new_token(char *token_str);
void			add_token(t_token_list *tl, char *token_str);

//syntax_err.c
int				is_syntax_err(t_token_list token_list);

#endif