/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:04:31 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 15:32:25 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "libft.h"
#include "safe_function.h"

static char	*get_empty_removal_limiter(char *unremoved)
{
	char	*limiter;
	int		len;
	char	last_quote;

	len = 0;
	last_quote = 0;
	while (*unremoved)
	{
		if (last_quote == 0 && (*unremoved == '\"' || *unremoved == '\''))
			last_quote = *unremoved;
		else if (last_quote == *unremoved)
			last_quote = 0;
		else
			++len;
		++unremoved;
	}
	limiter = malloc_s(len + 1);
	limiter[len] = 0;
	return (limiter);
}

char	*get_quote_removal_limiter(char *unremoved)
{
	int		idx;
	char	last_quote;
	char	*limiter;

	idx = -1;
	last_quote = 0;
	limiter = get_empty_removal_limiter(unremoved);
	while (*unremoved)
	{
		if (last_quote == 0 && (*unremoved == '\"' || *unremoved == '\''))
			last_quote = *unremoved;
		else if (last_quote == *unremoved)
			last_quote = 0;
		else
			limiter[++idx] = *unremoved;
		++unremoved;
	}
	return (limiter);
}

void	write_in_file(t_admin *hash_map, int fd, char *line, int have_to_expand)
{
	char	*expanded_line;

	if (have_to_expand)
	{
		expanded_line = get_param_expand_empty(hash_map, line);
		fill_param_expand(hash_map, line, expanded_line);
		write_s(fd, expanded_line, ft_strlen(expanded_line));
		write_s(fd, "\n", 1);
		free(expanded_line);
		return ;
	}
	write_s(fd, line, ft_strlen(line));
	write_s(fd, "\n", 1);
}
