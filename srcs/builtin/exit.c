/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:16:35 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 17:47:59 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	count_args(char **args);
static void	check_args(char **args);
long long	ft_atol(const char *str, int *flag);

int		builtin_exit(char **args)
{
	printf("exit\n");
	// ARGS상태를 점검하기.
	// 조건에 부합한다면, exit.
	// 조건에 부합하지 못한다면, return.
	check_args(args);
	return (1);
}

/*
	1. ARG[1] == NULL이라면, exit(0);
	2. ARG[1]이 적절한 값이면서, 인자가 딱 하나일때 is_unvalid_flag = 0; exit(ARG[1]);
	3. ARG[1]이 부적절한 값이면 is_unvalid_flag = 1; exit(255);
	4. ARG[1]이 적절한 값인데, 인자가 여러개라면, return (1);
*/

static void	check_args(char **args)
{
	int	return_value;		// 3번 경우 exit을 안할꺼야.
	int	is_unvalid_flag;	// args[1]이 옳은 값을 가지고 있는지 체크.
	int	arg_cnt;			// args의 개수를 체크

	arg_cnt = count_args(args);
	if (arg_cnt == 1) // 1번 경우.
		exit(0);
	is_unvalid_flag = 0;
	return_value = ft_atol(args[1], &is_unvalid_flag);
	if (is_unvalid_flag == 0 && arg_cnt == 2) // 2번 경우.
		exit(return_value);
	else if (is_unvalid_flag == 1) // 3번 경우.
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	printf("bash: exit: too many arguments\n"); // 4번 경우
}

static int	count_args(char **args)
{
	int arg_cnt;

	arg_cnt = 0;
	while (args[arg_cnt])
		arg_cnt++;
	return (arg_cnt);
}