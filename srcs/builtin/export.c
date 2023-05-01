/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:15:19 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/01 15:05:55 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "builtin.h"
#include "libft.h"
#include "list.h"

static int	inspect_arg(char *export_arg, int *return_val);
static int	is_error(char *arg, int *return_val);
static void	print_hash_map(t_admin *hash_map);

int	builtin_export(t_admin *hash_map, char ***envp, char **args)
{
	int	i;
	int	return_val;
	int	re_build_flag;

	i = 0;
	return_val = 0;
	re_build_flag = 0;
	if (args[1] == NULL)
		return (print_hash_map(hash_map), 0);
	while (args[++i])
	{
		if (inspect_arg(args[i], &return_val) == -1)
			continue ;
		add_node(hash_map, args[i]);
		re_build_flag = 1;
	}
	if (re_build_flag == 1)
		make_new_envp(hash_map, envp);
	return (return_val);
}

static int	inspect_arg(char *arg, int *return_val)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (is_error(arg, return_val));
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) || arg[i] == '_')
			i++;
		else
			return (is_error(arg, return_val));
	}
	return (0);
}

static int	is_error(char *arg, int *return_val)
{
	printf("minishell: export: %s: not a valid identifier\n", arg);
	*return_val = 1;
	return (-1);
}

static void	print_hash_map(t_admin *hash_map)
{
	int		i;
	t_node	*cur_node;

	i = -1;
	while (++i <= 52)
	{
		cur_node = hash_map[i].head->next;
		while (cur_node != hash_map[i].tail)
		{
			printf("%s", cur_node->key);
			if (cur_node->value != 0)
				printf("=\"%s\"\n", cur_node->value);
			else
				printf("\n");
			cur_node = cur_node->next;
		}
	}
}
