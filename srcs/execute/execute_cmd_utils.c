/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:40:49 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 01:01:54 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "list.h"
#include "libft.h"
#include "safe_function.h"

char	**get_path_list_from_env_path(t_admin *hash_map)
{
	t_node	*path_node;

	path_node = search_node(hash_map, "PATH");
	if (path_node == NULL)
		return (NULL);
	return (ft_split(path_node->value, ':'));
}

void	is_executable(char *cmd_with_path)
{
	if (access(cmd_with_path, F_OK) == -1 || ft_strchr(cmd_with_path, '/') == 0)
	{
		write_s(2, "bash: ", 7);
		write_s(2, cmd_with_path, ft_strlen(cmd_with_path));
		write_s(2, ": Command not found\n", 21);
		exit(127);
	}
	if (access(cmd_with_path, X_OK) == -1)
	{
		write_s(2, "bash: ", 7);
		write_s(2, cmd_with_path, ft_strlen(cmd_with_path));
		write_s(2, ": Permission denied\n", 21);
		exit(1);
	}
}

char	*get_path(char **path_list, char *cmd)
{
	if (path_list == NULL)
		return (ft_strdup(cmd));
	else
		return (find_path(path_list, cmd));
}

char	*find_path(char **path_list, char *cmd)
{
	int		i;
	char	*cmd_with_path;

	i = -1;
	while (path_list[++i])
	{
		cmd_with_path = char_join(path_list[i], cmd[0], '/');
		if (access(cmd_with_path, X_OK) == 0) // 존재하는 커맨드일 경우.
			return (cmd_with_path);
		free(cmd_with_path);
	}
	cmd_with_path = ft_strdup(cmd);
	if (cmd_with_path == NULL)
		MallocError();
	return (cmd_with_path);
}

char	*remove_outer_paren(char *prev_involve_paren)
{
	char	*involve_paren;

	involve_paren = ft_substr(prev_involve_paren, 1, ft_strlen(prev_involve_paren) - 2);
	if (involve_paren == NULL)
		malloc_error();
	free(prev_involve_paren);
	return (involve_paren);
}
