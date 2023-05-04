/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:23:40 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:12:45 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_function.h"
#include "libft.h"

int	builtin_env(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		write_s(1, (*envp)[i], ft_strlen((*envp)[i]));
		write_s(1, "\n", 1);
		i++;
	}
	return (0);
}
