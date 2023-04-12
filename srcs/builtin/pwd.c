/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:43:41 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 16:52:58 by dongyshi         ###   ########.fr       */
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
		_pwd = getcwd(NULL, 0);
		// if (_pwd == NULL)
			// ...? 뭐를 해야하지.
		printf("%s\n", _pwd);
	}
	else
		return (printf("%s\n", pwd->value), 0);
	return (0);
}