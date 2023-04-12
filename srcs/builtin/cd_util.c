/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:18:34 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 18:19:16 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	changing_oldpwd(t_admin *hash_map, t_node *pwd_node);
static void	changing_pwd(t_admin *hash_map, t_node *pwd_node, char *path_to_move);

int	using_env(t_admin *hash_map, char *path_to_move)
{
	t_node	*pwd_node;
	t_node	*oldpwd_node;
	char	*last_char;

	last_char = &path_to_move[ft_strlen(path_to_move) - 1];
	if (*last_char == '/')
		*last_char = '\0';
	pwd_node = search_node(hash_map, "PWD");
	if (pwd_node == NULL) // 경로를 변경할 수 없는 경우.
		return (1);
	oldpwd_node = search_node(hash_map, "OLDPWD");
	if (oldpwd_node != NULL)
		changing_oldpwd(hash_map, pwd_node);
	changing_pwd(hash_map, pwd_node, path_to_move);
	return (0); // 경로를 변경할 수 있는 경우
}

static void	changing_oldpwd(t_admin *hash_map, t_node *pwd_node)
{
	// pwd, oldpwd는 반드시 존재하는 노드
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", pwd_node->value);
	if (oldpwd == NULL)
		malloc_error();
	add_node(hash_map, oldpwd);
	free(oldpwd);
}

static void	changing_pwd(t_admin *hash_map, t_node *pwd_node, char *path_to_move)
{
	// pwd는 반드시 존재하는 노드
	char	*_pwd;
	char	*pwd;

	pwd = ft_strjoin("PWD=", pwd_node->value);\
	if (pwd == NULL)
		malloc_error();
	_pwd = pwd;
	pwd = ft_strjoin(pwd, "/");
	free(_pwd);
	_pwd = pwd;
	pwd = ft_strjoin(pwd, path_to_move);
	if (pwd == NULL)
		malloc_error();
	free(_pwd);
	add_node(hash_map, pwd);
	free(pwd);
}
