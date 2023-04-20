/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:57:12 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/20 19:08:20 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "list.h"
#include "parse.h"

typedef enum e_builtin_num
{
	cd = 31,
	echo,
	env,
	_exit,
	export,
	pwd,
	unset = 37
}			t_builtin_num;

//execute_minimal.c
int	execute_minimal(t_admin *hash_map, char ***envp, t_token *token, int is_pipe);
//execute_minimal_utils.c
char	*has_paren(t_token *token);
int		is_builtin(char *minimal_cmd);

//execute_cmd.c
int		execute_builtin_cmd(t_admin *hash_map, char ***envp, char **minimal_cmd, int builtin_num);
int		execute_non_builtin_cmd(t_admin *hash_map, char ***envp, char **minimal_cmd, int is_pipe);

//execute_cmd_utils.c
char	**get_path_list_from_env_path(t_admin *hash_map);
void	is_executable(char *cmd_with_path);
char	*get_path(char **path_list, char *cmd);
char	*find_path(char **path_list, char *cmd);




#endif