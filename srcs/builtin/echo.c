/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:57:10 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/23 20:25:07 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "list.h"
#include "libft.h"

static void	check_option(char **args, int *option_flag);
static int	print_args(char **args, int option_flag);

int	builtin_echo(char **args)
{
	int	option_flag;
	int	return_val;

	option_flag = 0;
	if (args[1] == NULL)
		write_s(1, "\n", 1);
	check_option(args, &option_flag);
	return_val = print_args(args, option_flag);
	if (option_flag == 0)
		write_s(1, "\n", 1);
	return (return_val);
}

static void	check_option(char **args, int *option_flag)
{
	if (ft_strncmp(args[1], "-n", 3) == 0)
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
		word_length != write_s(1, args[i], word_length);
		i++;
	}
	return (0);
}
