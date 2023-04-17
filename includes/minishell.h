/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:13:23 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/17 17:58:13 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "list.h"

void	make_hash_map(t_admin *hash_map, char *envp[], char ***new_envp);
void	make_new_envp(t_admin *hash_map, char ***envp);
char	*char_join(char *s1, char *s2, char c);
void	free_double_pointer(char **pptr);
void	malloc_error(void);

#endif
