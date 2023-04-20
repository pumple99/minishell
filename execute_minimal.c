/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:25:52 by seunghoy          #+#    #+#             */

/*   Updated: 2023/04/20 01
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"
#include "libft/libft.h"
#include <stdlib.h>


typedef enum e_builtin_num
{
	cd = 31,
	echo,
	env,
	exit,
	export,
	pwd,
	unset = 37
}			t_builtin_num;

static int	is_stop(t_token *token);
static int	is_redirection(t_token *token);
static int	count_array_size(t_token *token);
static int	is_builtin(char *minimal_cmd);

int	execute_minimal(t_token *token, int is_pipe)
{
	char	*involve_parel;
	char	**minimal_cmd;
	int		builtin_num;


	//execute_redirection
	involve_parel = has_paren(token);
	if (involve_parel)
		return (execute_subshell(involve_parel, is_pipe));
	else
	{
		// make char **
		// &&, ||, end, |만날때까지 실행시키고, 리다이렉션은 피하기.
		minimal_cmd = dmake_two_dimensional_array(token);
		builtin_num = is_builtin(minimal_cmd[0]);
		if (builtin_num)
			return (execute_builtin_cmd(minimal_cmd, builtin_num));
		else
			return (execute_non_builtin_cmd(minimal_cmd));
	}
	return (0);
}

char	*has_paren(t_token *token)
{
	int	parel_depth;

	parel_depth = 0;
	if (count_parel(token) == 0)
		return (NULL);
	while (is_stop(token))
	{
		if (token->type == paren_l)
			parel_depth++;
		else if (token->type == paren_r)
			parel_depth--;
		
	}
}


char	**make_two_dimensional_array(t_token *token)
{
	char	**cmd_arr;
	int		arr_size;
	int		idx;

	idx = 0;
	arr_size = count_array_size(token);
	cmd_arr = (char **)malloc(sizeof(char *) * (arr_size + 1));
	//if (cmd_arr == NULL)
		//malloc_error();
	cmd_arr[arr_size] = '\0';
	while (!is_stop(token))
	{
		if (is_redirection(token))
			token = token->next->next;
		else
		{
			cmd_arr[idx] = ft_strdup(token->string);
			//if (cmd_arr[idx] == NULL)
				//malloc_error();
		}
	}
}

static int	is_stop(t_token *token)
{
	if (token->type == and || token->type == or \
	|| token->type == _pipe || token->type == end)
		return (1);
	else
		return (0);
}

static int	is_redirection(t_token *token)
{
	if (token->type == redirect_r || token->type == redirect_l \
	|| token->type == append || token->type == heredoc)
		return (1);
	else
		return (0);
}

static int	count_array_size(t_token *token)
{
	int	cnt = 0;

	while (!is_stop(token))
	{
		if (is_redirection)
			token = token->next->next;
		else
		{
			++cnt;
			token = token->next;
		}
	}
	return (cnt);
}

static int	is_builtin(char *minimal_cmd)
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

int	execute_builtin_cmd(char **minimal_cmd, int builtin_num)
{
	// hash_map이 필요함.
	return ();
}

int	execute_non_builtin_cmd(char **minimal_cmd)
{

	return ();
}
