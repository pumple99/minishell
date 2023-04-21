/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:23:40 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/20 16:55:29 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	builtin_env(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}
