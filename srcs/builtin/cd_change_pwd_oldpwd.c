/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change_pwd_oldpwd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:53:30 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/22 21:51:34 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "libft.h"

static void	get_pwd_oldpwd_node(t_admin *hash_map, t_node **pwd_node, t_node **oldpwd_node);
static void	changing_oldpwd(t_admin *hash_map, t_node *pwd_node);
static void	changing_pwd(t_admin *hash_map, t_node *pwd_node, char *path_to_move);

void	changing_env(t_admin *hash_map, char *path_to_move, char *prev_directory)
{
	t_node	*pwd_node;
	t_node	*oldpwd_node;
	char	*last_char;

	last_char = &path_to_move[ft_strlen(path_to_move) - 1];
	if (*last_char == '/')
		*last_char = '\0';
	get_pwd_oldpwd_node(hash_map, &pwd_node, &oldpwd_node);
	if (oldpwd_node != NULL)
		changing_oldpwd(hash_map, pwd_node);
	if (pwd_node != NULL)
		changing_pwd(hash_map, pwd_node, path_to_move);
}

static void	get_pwd_oldpwd_node(t_admin *hash_map, t_node **pwd_node, t_node **oldpwd_node)
{
	*pwd_node = search_node(hash_map, "PWD");
	*oldpwd_node = search_node(hash_map, "OLDPWD");
}

static void	changing_oldpwd(t_admin *hash_map, t_node *pwd_node)
{
	char	*oldpwd;

	if (pwd_node == NULL)
	{
		add_node(hash_map, "OLDPWD=\"\"");
	}
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd_node->value);
		if (oldpwd == NULL)
			malloc_error();
		add_node(hash_map, oldpwd);
		free(oldpwd);
	}
}

static void	changing_pwd(t_admin *hash_map, t_node *pwd_node, char *path_to_move)
{
	char	*prev_pwd;
	char	*pwd;

	prev_pwd = ft_strjoin("PWD=", pwd_node->value);
	if (prev_pwd == NULL)
		malloc_error();
	pwd = char_join(prev_pwd, path_to_move, '/');
	if (pwd == NULL)
		malloc_error();
	free(prev_pwd);
	add_node(hash_map, pwd);
	free(pwd);
}