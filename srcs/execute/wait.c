/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:19:45 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 19:20:34 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	set_exit_status(int child_status, int *exit_status)
{
	int	status;

	status = 0;
	if (WIFEXITED(child_status))
		status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
		status = WTERMSIG(child_status);
	else if (WIFSTOPPED(child_status))
		status = WSTOPSIG(child_status);
	*exit_status = status;
}