/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:58:16 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 01:03:33 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute.h"
#include "libft/libft.h"
#include "builtin.h"
#include "safe_function.h"

static char	**make_two_dimensional_array(t_token *token);
static int	count_array_size(t_token *token);

int	execute_minimal(t_admin *hash_map, char ***envp, t_token *token, \
int is_pipe)
{
	char		*involve_paren_str;
	char		**minimal_cmd;
	int			builtin_num;
	t_fd_list	fd_list;

	fd_list = execute_redirection(token);
	if (fd_list.err)
		return (close_redirect_fds(fd_list, 1));
	involve_paren_str = has_paren(token);
	if (involve_paren_str)
		return (close_redirect_fds(fd_list, \
		execute_subshell(hash_map, involve_paren_str, envp, is_pipe)));
	else
	{
		minimal_cmd = make_two_dimensional_array(token);
		builtin_num = is_builtin(minimal_cmd[0]);
		if (builtin_num)
			return (close_redirect_fds(fd_list, \
			execute_builtin_cmd(hash_map, envp, minimal_cmd, builtin_num)));
		else
			return (close_redirect_fds(fd_list, \
			execute_non_builtin_cmd(hash_map, envp, minimal_cmd, is_pipe)));
	}
}

static char	**make_two_dimensional_array(t_token *token)
{
	char	**cmd_arr;
	int		arr_size;
	int		idx;

	idx = 0;
	arr_size = count_array_size(token);
	cmd_arr = (char **)malloc_s(sizeof(char *) * (arr_size + 1));
	while (!is_and_or_pipe_end(token))
	{
		if (is_redirection(token))
			token = token->next->next;
		else
		{
			cmd_arr[idx] = ft_strdup(token->string);
			if (cmd_arr[idx] == NULL)
				malloc_error();
			++idx;
			token = token->next;
		}
	}
	cmd_arr[arr_size] = '\0';
}

static int	count_array_size(t_token *token)
{
	int	cnt = 0;

	while (!is_and_or_pipe_end(token))
	{
		if (is_redirection(token))
			token = token->next->next;
		else
		{
			++cnt;
			token = token->next;
		}
	}
	return (cnt);
}
