/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_dir_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:14:09 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/22 20:39:08 by dongyshi         ###   ########.fr       */
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
	if (re != -1)
		return (re);
	perror("minishell: chdir failed");
}

int	closedir_s(DIR *dirp)
{
	int	re;

	re = closedir(dirp);
	if (re != -1)
		return (re);
	perror("minishell: closedir failed");
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
		if (prev_errno == errno)
			return (NULL);
		else
			perror("minishell: readdir failed");
	}
}
