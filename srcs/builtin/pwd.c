/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:43:41 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 16:00:15 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdio.h>
#include <unistd.h>

int	builtin_pwd(t_admin *hash_map)
{
	t_node	*pwd;
	char	*_pwd;

	pwd = search_node(hash_map, "PWD");
	if (pwd == NULL)
	{
		_pwd = getcwd_s(NULL, 0);
		// if (_pwd == NULL)
			// ...? 뭐를 해야하지.
		printf("%s\n", _pwd);
	}
	else
		return (printf("%s\n", pwd->value), 0);
	return (0);
}