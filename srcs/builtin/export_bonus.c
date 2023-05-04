/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:15:19 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:12:49 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "safe_function_bonus.h"
#include "builtin_bonus.h"
#include "libft.h"
#include "list_bonus.h"

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
	write_s(2, "minishell: export: ", 20);
	write_s(2, arg, ft_strlen(arg));
	write_s(2, ": not a valid identifier\n", 26);
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
			write_s(1, cur_node->key, ft_strlen(cur_node->key));
			if (cur_node->value != 0)
			{
				write_s(1, "=\"", 3);
				write_s(1, cur_node->value, ft_strlen(cur_node->value));
				write_s(1, "\"\n", 3);
			}
			else
				write_s(1, "\n", 2);
			cur_node = cur_node->next;
		}
	}
}
