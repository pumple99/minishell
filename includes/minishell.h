/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:13:23 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:56 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"

//utils.c
char	*char_join(char *s1, char *s2, char c);
void	free_double_pointer(char **pptr);

//main_conf.c
void	config(void);
void	sigint(int signum);

//main_utils.c
void	delete_hash_map(t_admin *hash_map);
void	delete_new_envp(char ***new_envp_ptr);
void	is_exec_subshell(t_admin *hash_map, char *argv[], char ***envp);

#endif
