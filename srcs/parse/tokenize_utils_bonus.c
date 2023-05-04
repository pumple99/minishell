/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:36:45 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 17:16:58 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"
#include "libft.h"

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

t_token_type	get_token_type(char *str)
{
	if (ft_strncmp(str, "(", 2) == 0)
		return (paren_l);
	else if (ft_strncmp(str, ")", 2) == 0)
		return (paren_r);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (redirect_r);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (redirect_l);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (append);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (heredoc);
	else if (ft_strncmp(str, "&&", 3) == 0)
		return (and);
	else if (ft_strncmp(str, "||", 3) == 0)
		return (or);
	else if (ft_strncmp(str, "|", 2) == 0)
		return (_pipe);
	else
		return (word);
}
