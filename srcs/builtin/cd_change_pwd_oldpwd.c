/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change_pwd_oldpwd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:53:30 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/03 19:59:11 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "libft.h"
#include "minishell.h"
#include "safe_function.h"

static void	get_pwd_oldpwd_node(t_admin *hash_map, t_node **pwd_node, \
t_node **oldpwd_node);
static void	changing_oldpwd(t_admin *hash_map, t_node *pwd_node);
static void	changing_pwd(t_admin *hash_map, t_node *pwd_node, \
						char *path_to_move);
static int	using_getcwd(t_admin *hash_map, char *prev_path);

void	changing_env(t_admin *hash_map, char *path_to_move, char *prev_path)
{
	t_node	*pwd_node;
	t_node	*oldpwd_node;
	char	*last_char;

	last_char = &path_to_move[ft_strlen(path_to_move) - 1];
	if (*last_char == '/')
		*last_char = '\0';
	get_pwd_oldpwd_node(hash_map, &pwd_node, &oldpwd_node);
	if (using_getcwd(hash_map, prev_path))
		return ;
	if (oldpwd_node != NULL)
		changing_oldpwd(hash_map, pwd_node);
	if (pwd_node != NULL)
		changing_pwd(hash_map, pwd_node, path_to_move);
}

static int	using_getcwd(t_admin *hash_map, char *prev_path)
{
	char	*prev_pwd;
	char	*pwd;
	char	*oldpwd;

	prev_pwd = getcwd(NULL, 0);
	if (prev_pwd == NULL)
		return (0);
	pwd = char_join("PWD", prev_pwd, '=');
	free(prev_pwd);
	add_node(hash_map, pwd);
	oldpwd = char_join("OLDPWD", prev_path, '=');
	add_node(hash_map, oldpwd);
	free(pwd);
	free(oldpwd);
	return (1);
}

static void	get_pwd_oldpwd_node(t_admin *hash_map, t_node **pwd_node, \
t_node **oldpwd_node)
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
		oldpwd = char_join("OLDPWD", pwd_node->value, '=');
		add_node(hash_map, oldpwd);
		free(oldpwd);
	}
}

static void	changing_pwd(t_admin *hash_map, t_node *pwd_node, \
						char *path_to_move)
{
	char	*prev_pwd;
	char	*pwd;

	prev_pwd = char_join("PWD", pwd_node->value, '=');
	pwd = char_join(prev_pwd, path_to_move, '/');
	add_node(hash_map, pwd);
	free(prev_pwd);
	free(pwd);
}
