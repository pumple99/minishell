/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:27:13 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 00:52:01 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "minishell.h"

int	builtin_unset(t_admin *hash_map, char ***envp, char **args)
{
	int		i;
	int		re_build_flag;

	if (args == NULL)
		return (0);
	i = -1;
	re_build_flag = 0;
	while (args[++i])
		delete_node(hash_map, args[i], &re_build_flag);
	if (re_build_flag == 1)
		make_new_envp(hash_map, envp);
	return (0);
}
