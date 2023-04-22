/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:07:53 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/22 21:50:59 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "safe_function.h"
#include "builtin.h"
#include "list.h"
#include "libft.h"
#include "minishell.h"

static int	is_movable(char *arg);

char	*make_path(t_admin *hash_map, char *arg)
{
	char	*path_to_move;

	path_to_move = NULL;
	if (arg[0] != '.')
		path_to_move = using_cdpath(hash_map, arg);
	if (path_to_move != NULL)
	{
		write_s(1, path_to_move, ft_strlen(path_to_move));
		write_s(1, "\n", 1);
		return (path_to_move);
	}
	else
	{
		if (is_movable(arg))
			return (ft_strdup(arg));
	}
	return (NULL);
}

char	*using_cdpath(t_admin *hash_map, char *arg)
{
	t_node	*cdpath_node;
	char	**cdpath_list;
	char	*path_to_move;
	int		i;

	cdpath_node = search_node(hash_map, "CDPATH");
	if (cdpath_node == NULL)
		return (NULL);
	cdpath_list = ft_split(cdpath_node->value, ':');
	if (cdpath_list == NULL)
		malloc_error();
	i = -1;
	while (cdpath_list[++i])
	{
		if (cdpath_list[i][ft_strlen(cdpath_list[i]) - 1] != '/')
			path_to_move = char_join(cdpath_list[i], arg, '/');
		else
			path_to_move = ft_strjoin(path_to_move, arg);
		if (access(path_to_move, X_OK) == 0)
			return (free_double_pointer(cdpath_list), path_to_move);
		free(path_to_move);
	}
	return (free_double_pointer(cdpath_list), NULL);
}

static int	is_movable(char *arg)
{
	int		file_exist;
	int		file_permission;

	file_exist = access(arg, F_OK);
	if (file_exist == -1)
	{
		write_s(2, "bash: cd: ", 11);
		write_s(2, arg, ft_strlen(arg));
		write_s(2, ": No such file or directory\n", 29);
		return (0);
	}
	file_permission = access(arg, X_OK);
	if (file_permission == -1)
	{
		write_s(2, "bash: cd: ", 11);
		write_s(2, arg, ft_strlen(arg));
		write_s(2, ": Permission denied\n", 21);
		return (0);
	}
	return (1);
}
