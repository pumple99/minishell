/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:17:33 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 17:50:37 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "main.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*make_path(t_admin *hash_map, char *arg);
static char	*using_cdpath(t_admin *hash_map, char *arg);
static int	is_movable(char *arg);
static void	changing_env(t_admin *hash_map, char *path_to_move, char *prev_pwd);
static void	changing_pwd(t_admin *hash_map);
static void	changing_oldpwd(t_admin *hash_map, char *prev_pwd);
int			using_env(t_admin *hash_map, char *path_to_move);
static void	free_param(char *pwd, char *path_to_move);

// "getcwd"가 오류날 경우에 대한 체크 아직 못함.
// "chdir"가 오류날 경우에 대한 체크 아직 못함.
// 현재 디렉토리가 존재하지 않고, 그리고 ".." or "."를 할 경우 pwd를 교체하는 경우

int	builtin_cd(t_admin *hash_map, char ***envp, char **args)
{
	char	*path_to_move;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	// if (pwd == NULL) // 현재 디렉토리가 삭제된 경우. => 처리 필요함,
	// 	printf("%s", "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	if (args[1] == NULL)
		return (0);
	path_to_move = make_path(hash_map, args[1]); // 이동할 문자열을 생성하기.
	if (path_to_move == NULL) // 생성한 문자열을 가지고, 이동 가능한지 체크하기.
		return (free_param(pwd, path_to_move), 1);
	if (chdir(path_to_move) == 0) // chdir은 잘 실행이 되었으면 0리턴, 아니면 -1;
	{
		changing_env(hash_map, path_to_move, pwd); // pwd, oldpwd수정하기.
		make_new_envp(hash_map, envp); // pwd와, oldpwd가 변했으므로 새롭게 환경변수 세팅하기
	}
	// else //chdir함수가 오류가 날 경우.
		// return (1);
	return (free_param(pwd, path_to_move), 0);
}

static char	*make_path(t_admin *hash_map, char *arg)
{
	char	*path_to_move;

	path_to_move = NULL;
	if (arg[0] != '.')
		path_to_move = using_cdpath(hash_map, arg);
	if (path_to_move != NULL)
		return (printf("%s\n", path_to_move), path_to_move); // CDPATH를 사용할때는 절대경로 출력 해야함.
	else
		if (is_movable(arg))
			return (ft_strdup(arg));
	return (NULL);
}

static char	*using_cdpath(t_admin *hash_map, char *arg)
{
	t_node	*cdpath_node;
	char	**cdpath_list;
	char	*prev_path;
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
			path_to_move = ft_strjoin(cdpath_list[i], "/");
		prev_path = path_to_move;
		path_to_move = ft_strjoin(path_to_move, arg);
		free(prev_path);
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
		write(2, "bash: cd: ", 11);
		write(2, arg, ft_strlen(arg));
		write(2, ": No such file or directory\n", 29);
		return (0);
	}
	file_permission = access(arg, X_OK);
	if (file_permission == -1)
	{
		write(2, "bash: cd: ", 11);
		write(2, arg, ft_strlen(arg));
		write(2, ": Permission denied\n", 21);
		return (0);
	}
	return (1);
}

static void	changing_env(t_admin *hash_map, char *path_to_move, char *prev_pwd)
{
	int	cant_change;
	// 여기에 들어오는 경우에는, 반드시!!!!!!!!! arg가 이동 가능한 변수일때만 들어온다
	// path_to_move는 이동 가능한 상대경로 일때만 들어올 수 있음.
	cant_change = 0;
	if (prev_pwd != NULL)
	{
		changing_pwd(hash_map);
		changing_oldpwd(hash_map, prev_pwd);
	}
	else
		cant_change = using_env(hash_map, path_to_move);
	// if (cant_change) // 아예 바꾸지 못하는 경우
		// do something
}

static void	changing_pwd(t_admin *hash_map)
{
	t_node	*pwd_node;
	char	*pwd;
	char	*_pwd;

	pwd_node = search_node(hash_map, "PWD");
	if (pwd_node != NULL)
	{
		pwd = getcwd(NULL, 0);
		// if (pwd == NULL)
			// do something
		_pwd = pwd;
		pwd = ft_strjoin("PWD=", pwd);
		free(_pwd);
		add_node(hash_map, pwd);
	}
}

static void	changing_oldpwd(t_admin *hash_map, char *prev_pwd)
{
	t_node	*oldpwd_node;
	char	*_oldpwd;
	char	*oldpwd;

	oldpwd_node = search_node(hash_map, "OLDPWD");
	if (oldpwd_node != NULL)
	{
		oldpwd = ft_strdup(prev_pwd);
		if (oldpwd == NULL)
			malloc_error();
		_oldpwd = oldpwd;
		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		free(_oldpwd);
		add_node(hash_map, oldpwd);
	}
}

static void	free_param(char *pwd, char *path_to_move)
{
	if (pwd != NULL)
		free(pwd);
	if (path_to_move)
		free(path_to_move);
}