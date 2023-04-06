/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:36:45 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/06 20:04:38 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../libft/libft.h"

int	is_arr_size_plus(t_state prev, t_state new)
{
	if (new.num_s == op_may_change || new.num_s == op_paren)
		return (1);
	else if ((prev.num_s == outside || prev.num_s == op_end || \
		prev.num_s == op_paren || prev.num_s == op_may_change) && \
		(new.num_s == inside || new.num_s == quote))
		return (1);
	return (0);
}

int	is_pre_break_condition(t_state prev, t_state new)
{
	if (new.num_s == outside)
		return (1);
	else if (prev.num_s == inside && \
	(new.num_s == op_may_change || new.num_s == op_paren))
		return (1);
	else if (prev.num_s == op_may_change && new.num_s != op_end)
		return (1);
	return (0);
}

void	allocate_token_type(t_token *token_arr, int arr_idx)
{
	char	*str;

	str = token_arr[arr_idx].string;
	if (ft_strncmp(str, "(", 2) == 0)
		token_arr[arr_idx].type = paren_l;
	else if (ft_strncmp(str, ")", 2) == 0)
		token_arr[arr_idx].type = paren_r;
	else if (ft_strncmp(str, ">", 2) == 0)
		token_arr[arr_idx].type = redirect_r;
	else if (ft_strncmp(str, "<", 2) == 0)
		token_arr[arr_idx].type = redirect_l;
	else if (ft_strncmp(str, ">>", 3) == 0)
		token_arr[arr_idx].type = append;
	else if (ft_strncmp(str, "<<", 3) == 0)
		token_arr[arr_idx].type = heredoc;
	else if (ft_strncmp(str, "&&", 3) == 0)
		token_arr[arr_idx].type = and;
	else if (ft_strncmp(str, "||", 3) == 0)
		token_arr[arr_idx].type = or;
	else if (ft_strncmp(str, "|", 2) == 0)
		token_arr[arr_idx].type = pipe;
	else
		token_arr[arr_idx].type = word;
}

t_token	*free_parse_arr(t_token *token_arr, int arr_idx)
{
	//need change
	return (0);
}