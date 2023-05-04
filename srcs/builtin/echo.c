/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:57:10 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:12:40 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "safe_function.h"

static int	check_option(char **args, int *option_flag);
static int	print_args(int i, char **args);

int	builtin_echo(char **args)
{
	int	option_flag;
	int	return_val;
	int	i;

	option_flag = 0;
	if (args[1] == NULL)
	{
		write_s(1, "\n", 1);
		return (0);
	}
	i = check_option(args, &option_flag);
	return_val = print_args(i, args);
	if (option_flag == 0)
		write_s(1, "\n", 1);
	return (return_val);
}

static int	check_option(char **args, int *option_flag)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][0] == '-')
		{
			while (args[i][++j])
			{
				if (args[i][j] != 'n')
					return (i);
			}
			if (j == 1)
				return (i);
		}
		else
			break ;
		*option_flag = 1;
	}
	return (i);
}

static int	print_args(int i, char **args)
{
	while (args[i])
	{
		write_s(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write_s(1, " ", 1);
		i++;
	}
	return (0);
}
