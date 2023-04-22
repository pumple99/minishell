/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_dir_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:14:09 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/22 21:47:26 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include <sys/errno.h>
#include "../../includes/safe_function.h"

int chdir_s(const char *path)
{
	int re;

	re = chdir(path);
	if (re == -1)
		perror("minishell: chdir failed");
	return (re);
}

int	closedir_s(DIR *dirp)
{
	int	re;

	re = closedir(dirp);
	if (re == -1)
		perror("minishell: closedir failed");
	return (re);
}

struct dirent	*readdir_s(DIR *dirp)
{
	struct dirent	*re;
	int				prev_errno;

	prev_errno = errno;
	re = readdir(dirp);
	if (readdir != NULL) 
		return (re);
	else
	{
		if (prev_errno != errno)
			perror("minishell: readdir failed");
		return (NULL);
	}
}
