/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:19:27 by sindong-yeo       #+#    #+#             */
/*   Updated: 2023/04/23 19:15:09 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse_bonus.h"

static int	is_wildcard(t_match *values, char *pattern);
static void	init_values(t_match *values, char *string, char *pattern);
static int	is_over(t_match *values, char *pattern);

int is_match(char *string, char *pattern)
{
	t_match	values;

	init_values(&values, string, pattern);
	while (values.string_index < values.string_len)
	{
		if (is_wildcard(&values, pattern))
			continue ;
		if (values.pattern_index < values.pattern_len \
		&& ((pattern[values.pattern_index] == string[values.string_index]) \
		|| (pattern[values.pattern_index] == -1 && string[values.string_index] == '*')))
		{
			++values.string_index;
			++values.pattern_index;
		}
		else if (values.last_wildcard_idx == -1)
			return 0;
		else
		{
			values.pattern_index = values.next_to_wildcard_idx;
			values.string_index = ++values.str_backtrack_idx;
		}
	}
	return (is_over(&values, pattern));
}

static void	init_values(t_match *values, char *string, char *pattern)
{
	values->string_index = 0;
	values->pattern_index = 0;
	values->last_wildcard_idx = -1;
	values->str_backtrack_idx = -1;
	values->next_to_wildcard_idx = -1;
	values->string_len = ft_strlen(string);
	values->pattern_len = ft_strlen(pattern);
	if (pattern[values->pattern_len - 1] == '/')
		--values->pattern_len;
}

static int	is_over(t_match *values, char *pattern)
{
	int i;

	i = values->pattern_index;
	while (i < values->pattern_len)
	{
		if (pattern[i] != '*')
			return 0;
		i++;
	}
	return (1);
}

static int	is_wildcard(t_match *values, char *pattern)
{
	if (values->pattern_index < values->pattern_len && pattern[values->pattern_index] == '*')
	{
		values->last_wildcard_idx = values->pattern_index;
		values->next_to_wildcard_idx = ++values->pattern_index;
		values->str_backtrack_idx = values->string_index;
		return (1);
	}
	return (0);
}
