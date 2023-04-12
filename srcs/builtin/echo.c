/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:57:10 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/12 16:52:36 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

/*
	1. args를 공백으로 분리해서 출력하고, 개행으로 종료시키기!
	2. write 실패 시 오류 출력. (0보다 작은 값을 리턴한다.) 성공 시 0리턴.
	3. -n옵션 존재 시 개행을 제거한다.
	4. 옵션은 반드시 args[1]에 존재해야한다.
*/

static void	check_option(char **args, int *option_flag);
static int	print_args(char **args, int option_flag);

int	builtin_echo(char **args)
{
	int	option_flag;
	int	return_val;

	option_flag = 0;
	if (args[1] == NULL)
		write(1, "\n", 1);
	check_option(args, &option_flag); // 옵션의 유무를 확인하고, 출력할 문자열들의 전제 길이를 체크한다.
	return_val = print_args(args, option_flag);
	if (option_flag == 0)
		write(1, "\n", 1);
	return (return_val);
}

static void	check_option(char **args, int *option_flag)
{
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
		*option_flag = 1;
}

static int	print_args(char **args, int option_flag)
{
	int	i;
	int	word_length;

	if (option_flag == 0)
		i = 1;
	else
		i = 2;
	while (args[i])
	{
		word_length = ft_strlen(args[i]);
		if (word_length != write(1, args[i], word_length))
		{
			// write error가 발생한 부분 어떻게 처리할지 생각해보기.
			return (-1);
		}
		i++;
	}
	return (0);
}