/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minimal_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:24:08 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/24 21:05:35 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "safe_function.h"

static int	count_paren(t_token *token);
static void	make_involve_paren(char **involve_paren, char *new_string);

int	is_builtin(char *minimal_cmd)
{
	if (ft_strncmp(minimal_cmd, "cd", 3) == 0)
		return (cd);
	else if (ft_strncmp(minimal_cmd, "echo", 5) == 0)
		return (echo);
	else if (ft_strncmp(minimal_cmd, "env", 4) == 0)
		return (env);
	else if (ft_strncmp(minimal_cmd, "exit", 5) == 0)
		return (__exit);
	else if (ft_strncmp(minimal_cmd, "export", 7) == 0)
		return (export);
	else if (ft_strncmp(minimal_cmd, "pwd", 4) == 0)
		return (pwd);
	else if (ft_strncmp(minimal_cmd, "unset", 6) == 0)
		return (unset);
	else
		return (0);
}

char	*has_paren(t_token *token)
{
	char	*involve_paren_str;
	int		paren_depth;

	if (count_paren(token) == 0)
		return (NULL);
	paren_depth = 0;
	involve_paren_str = ft_strdup_s("");
	while (token->type != end)
	{
		if (paren_depth == 0 && is_and_or_pipe_end(token))
			break ;
		if (token->type == paren_l)
			++paren_depth;
		else if (token->type == paren_r)
			--paren_depth;
		make_involve_paren(&involve_paren_str, token->string);
		token = token->next;
	}
	return (remove_outer_paren(involve_paren_str));
}

static int	count_paren(t_token *token)
{
	int	cnt;
	int	paren_depth;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && is_and_or_pipe_end(token))
			break ;
		if (token->type == paren_l)
		{
			++paren_depth;
			return (1);
		}
		else if (token->type == paren_r)
			--paren_depth;
		token = token->next;
	}
	return (0);
}

static void	make_involve_paren(char **involve_paren_str, char *new_string)
{
	char	*prev_involve_paren;

	prev_involve_paren = *involve_paren_str;
	*involve_paren_str = char_join(*involve_paren_str, new_string, ' ');
	free(prev_involve_paren);
}
