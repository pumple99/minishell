/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minimal_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:24:08 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/21 15:20:51 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "execute.h"

static int	count_paren(t_token *token);
static void	make_involve_paren(char **involve_paren, char *new_string);
static char	*remove_outer_paren(char *prev_involve_paren);

int	is_builtin(char *minimal_cmd)
{
	char	*cmd_len;

	cmd_len = ft_strlen(minimal_cmd);
	if (ft_strncmp(minimal_cmd, "cd", cmd_len) == 0)
		return (cd);
	else if (ft_strncmp(minimal_cmd, "echo", cmd_len) == 0)
		return (echo);
	else if (ft_strncmp(minimal_cmd, "env", cmd_len) == 0)
		return (env);
	else if (ft_strncmp(minimal_cmd, "exit", cmd_len) == 0)
		return (exit);
	else if (ft_strncmp(minimal_cmd, "export", cmd_len) == 0)
		return (export);
	else if (ft_strncmp(minimal_cmd, "pwd", cmd_len) == 0)
		return (pwd);
	else if (ft_strncmp(minimal_cmd, "unset", cmd_len) == 0)
		return (unset);
	else
		return (0);
}

char	*has_paren(t_token *token)
{
	char	*involve_paren;
	int		paren_depth;

	if (count_paren(token) == 0)
		return (NULL);
	paren_depth = 0;
	involve_paren = ft_strdup("");
	if (involve_paren == NULL)
		malloc_error();
	while (token->type != end)
	{
		if (paren_depth == 0 && is_and_or_pipe_end(token))
			break;
		if (token->type == paren_l)
			++paren_depth;
		else if (token->type == paren_r)
			--paren_depth;
		make_involve_paren(&involve_paren, token->string);
		token = token->next;
	}
	return (remove_outer_paren(involve_paren));
}

static int	count_paren(t_token *token)
{
	int	cnt;
	int	paren_depth;

	paren_depth = 0;
	while (token->type != end)
	{
		if (paren_depth == 0 && is_and_or_pipe_end(token))
			break;
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

static void	make_involve_paren(char **involve_paren, char *new_string)
{
	char	*prev_involve_paren;

	prev_involve_paren = *involve_paren;
	*involve_paren = char_join(*involve_paren, new_string, ' ');
	if (*involve_paren == NULL)
		malloc_error();
	free(prev_involve_paren);
}

static char	*remove_outer_paren(char *prev_involve_paren)
{
	char	*involve_paren;

	involve_paren = ft_substr(prev_involve_paren, 1, ft_strlen(prev_involve_paren) - 2);
	if (involve_paren == NULL)
		malloc_error();
	free(prev_involve_paren);
	return (involve_paren);
}
