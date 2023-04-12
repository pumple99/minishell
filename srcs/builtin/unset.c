/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:27:13 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 16:52:59 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "main.h"
#include <stdlib.h>

int	builtin_unset(t_admin *hash_map, char ***envp, char **args)
{
	int		i;
	int		re_build_flag;

	if (args == NULL) // 아무런 매개변수도 들어오지 않은 경우
		return (0);
	i = -1;
	re_build_flag = 0;
	while (args[++i])
		delete_node(hash_map, args[i], &re_build_flag);
	if (re_build_flag == 1)
		make_new_envp(hash_map, envp);
	return (0);
}