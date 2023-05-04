/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:17:33 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:12:38 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "safe_function.h"
#include "builtin.h"
#include "list.h"

static void	free_param(char *pwd, char *path_to_move);

int	builtin_cd(t_admin *hash_map, char ***envp, char **args)
{
	char	*path_to_move;
	char	*pwd;

	if (args[1] == NULL)
		return (0);
	pwd = getcwd_s(NULL, 0);
	path_to_move = make_path(hash_map, args[1]);
	if (path_to_move == NULL)
		return (free_param(pwd, path_to_move), 1);
	if (chdir_s(path_to_move) == 0)
	{
		changing_env(hash_map, path_to_move, pwd);
		make_new_envp(hash_map, envp);
	}
	return (free_param(pwd, path_to_move), 0);
}

static void	free_param(char *pwd, char *path_to_move)
{
	if (pwd)
		free(pwd);
	if (path_to_move)
		free(path_to_move);
}
