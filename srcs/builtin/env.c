/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:23:40 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/05 02:50:57 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	env(char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}
