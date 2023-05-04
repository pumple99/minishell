/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:33:13 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:12:47 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int			ft_isdigit(int c);
static long long	get_res(const char *str, long long res, \
int sign, int *flag);

long long	ft_atol(const char *str, int *flag)
{
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
	{
		*flag = 1;
		return (0);
	}
	return (get_res(str, res, sign, flag));
}

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static long long	get_res(const char *str, long long res, int sign, int *flag)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			*flag = 1;
		if (res > 922337203685477580)
			*flag = 1;
		else if (res == 922337203685477580 && *str >= '7' && sign == 1)
			*flag = 1;
		else if (res == 922337203685477580 && *str > '7' && sign == -1)
			*flag = 1;
		if (*flag == 1)
			break ;
		res = (res * 10) + (*str - '0');
			str++;
	}
	res *= sign;
	return (res);
}
