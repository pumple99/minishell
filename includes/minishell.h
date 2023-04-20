/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:13:23 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/20 18:56:25 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "list.h"

char	*char_join(char *s1, char *s2, char c);
void	free_double_pointer(char **pptr);
void	malloc_error(void);

#endif
