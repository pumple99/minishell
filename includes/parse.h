/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:11:43 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/05 19:04:25 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

//quote includes double quote
typedef enum e_num_state
{
	outside = 0,
	inside,
	quote,
	ampersand,
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
	word,
	operation
}	t_token_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
}	t_token;

t_state	get_new_state(t_state prev_state, char c);

#endif