/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minimal_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:24:08 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/20 19:04:41 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "execute.h"

static int	count_paren(t_token *token);
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
		if (paren_depth == 0 && is_or_and_end(token))
			break;
		if (token->type == paren_l)
			++paren_depth;
		else if (token->type == paren_r)
			--paren_depth;
		involve_paren = ft_strjoin(involve_paren, token->string);
		if (involve_paren == NULL)
			malloc_error();
		token = token->next;
	}
	return (remove_outer_paren(involve_paren));
}

static int	count_paren(t_token *token)
{
	int	cnt;

	while (token->type != end)
	{
		if (token->type == paren_l)
			return (1);
		token = token->next;
	}
	return (0);
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
