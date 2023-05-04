/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:23:40 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 16:02:47 by seunghoy         ###   ########.fr       */
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
