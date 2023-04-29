/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:16:35 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/29 17:51:32 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "safe_function.h"

static int	count_args(char **args);
static void	check_args(char **args);
static int	is_no_arg(int arg_cnt);
long long	ft_atol(const char *str, int *flag);

int	builtin_exit(char **args)
{
	write_s(1, "exit\n", 5);
	check_args(args);
	return (1);
}

static void	check_args(char **args)
{
	int	return_value;
	int	is_unvalid_flag;
	int	arg_cnt;

	arg_cnt = count_args(args);
	if (is_no_arg(arg_cnt))
		exit(0);
	is_unvalid_flag = 0;
	return_value = ft_atol(args[1], &is_unvalid_flag);
	if (is_unvalid_flag == 1)
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	else if (arg_cnt > 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	exit(return_value);
}

static int	count_args(char **args)
{
	int	arg_cnt;

	arg_cnt = 0;
	while (args[arg_cnt])
		arg_cnt++;
	return (arg_cnt);
}

static int	is_no_arg(int arg_cnt)
{
	if (arg_cnt == 1)
		return (1);
	else
		return (0);
}
