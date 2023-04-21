/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:57:10 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/20 15:58:22 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

static void	check_option(char **args, int *option_flag);
static int	print_args(char **args, int option_flag);

int	builtin_echo(char **args)
{
	int	option_flag;
	int	return_val;

	option_flag = 0;
	if (args[1] == NULL)
		write(1, "\n", 1);
	check_option(args, &option_flag);
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