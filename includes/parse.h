/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:11:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/06 21:51:49 by seunghoy         ###   ########.fr       */
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
}	t_token;

typedef enum e_syntax_s
{
	none = 20,
	exist,
	a_bracket,
	done,
	done_a_bracket,
	error
}	t_syntax_s;

// typedef struct s_syntax_s
// {
// 	int		paren_depth;
// 	t_syntax_num_s	
// }	t_syntax_s;

//tokenize_state.c
t_state	get_new_state(t_state prev_state, char *str);
t_state	init_state(void);

//tokenize_utils.c
int		is_arr_size_plus(t_state prev, t_state new);
int		is_pre_break_condition(t_state prev, t_state new);
void	allocate_token_type(t_token *token_arr, int arr_idx);
t_token	*free_parse_arr(t_token *token_arr, int arr_idx);

#endif