/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:15:19 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/06 16:43:34 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	inspect_arg(char *export_arg, int *flag);

int	export(t_admin *hash_map, char ***envp, char **export_args)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (export_args == NULL)
		return (print_hash_map(hash_map), 0);
	while (export_args[++i])
	{
		if (inspect_arg(export_args[i], &flag) == -1)
			continue ;
		add_node(hash_map, export_args[i]);
	}
	make_array(hash_map, envp);
	return (flag);
}

static int	inspect_arg(char *export_arg, int *flag)
{
	if (('A' <= export_arg[0] && export_arg[0] <= 'Z') \
		|| ('a' <= export_arg[0] && export_arg[0] <= 'z') \
		|| ('_' == export_arg[0]))
		return (0);
	*flag = 1;
	return (-1);
}
