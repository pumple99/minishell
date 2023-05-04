/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:43:41 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 15:58:58 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "list.h"
#include "libft.h"
#include "safe_function.h"

int	builtin_pwd(t_admin *hash_map)
{
	t_node	*pwd_node;
	char	*pwd;

	pwd_node = search_node(hash_map, "PWD");
	if (pwd_node == NULL)
	{
		pwd = getcwd_s(NULL, 0);
		write_s(1, pwd, ft_strlen(pwd));
		write_s(1, "\n", 1);
	}
	else
	{
		write_s(1, pwd_node->value, ft_strlen(pwd_node->value));
		write_s(1, "\n", 1);
	}
	return (0);
}
