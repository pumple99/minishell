/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:40:49 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/20 19:08:33 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "list.h"
#include "libft.h"

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
	if (access(cmd_with_path, F_OK) == -1)
	{
		write(2, "bash: ", 7);
		write(2, cmd_with_path, ft_strlen(cmd_with_path));
		write(2, ": Command not found\n", 21);
		exit(127);
	}
	if (access(cmd_with_path, X_OK) == -1)
	{
		write(2, "bash: ", 7);
		write(2, cmd_with_path, ft_strlen(cmd_with_path));
		write(2, ": Permission denied\n", 21);
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
	char	*path_cmd;

	i = -1;
	while (path_list[++i])
	{
		path_cmd = char_join(path_list[i], cmd[0], '/');
		if (path_cmd == NULL)
			MallocError();
		if (access(path_cmd, X_OK) == 0) // 존재하는 커맨드일 경우.
			return (path_cmd);
		free(path_cmd);
	}
	path_cmd = ft_strdup(cmd);
	if (path_cmd == NULL)
		MallocError();
	return (path_cmd);
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