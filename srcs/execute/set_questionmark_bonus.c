/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_questionmark_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:41:59 by sindong-yeo       #+#    #+#             */
/*   Updated: 2023/05/04 17:18:32 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_bonus.h"
#include "list_bonus.h"
#include "libft.h"

void	set_questionmark(t_admin *hash_map, int exit_status)
{
	char	*exit_status_char;
	char	*prev_exit_status_char;

	exit_status_char = ft_itoa(exit_status);
	prev_exit_status_char = exit_status_char;
	exit_status_char = char_join("?", exit_status_char, '=');
	add_node(hash_map, exit_status_char);
	free(exit_status_char);
	free(prev_exit_status_char);
}
