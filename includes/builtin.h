/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:51:54 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:51 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "list.h"

//builtin
int			builtin_env(char ***envp);
int			builtin_export(t_admin *hash_map, char ***envp, char **export_args);
int			builtin_unset(t_admin *hash_map, char ***envp, char **args);
int			builtin_exit(t_admin *hash_map, char **args);
int			builtin_cd(t_admin *hash_map, char ***envp, char **args);
int			builtin_pwd(t_admin *hash_map);
int			builtin_echo(char **args);

//cd_find_path.c
char		*make_path(t_admin *hash_map, char *arg);
char		*using_cdpath(t_admin *hash_map, char *arg);

//cd_change_pwd_oldpwd.c
void		changing_env(t_admin *hash_map, char *path_to_move, char *prev_pwd);

//exit_utils.c
long long	ft_atol(const char *str, int *flag);

//make_hash_map.c
void		make_hash_map(t_admin *hash_map, char *envp[], char ***new_envp);

//make_new_envp.c
void		make_new_envp(t_admin *hash_map, char ***envp);

#endif
