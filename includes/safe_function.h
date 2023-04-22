/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:39:05 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/22 20:43:10 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_FUNCTION
# define SAFE_FUNCTION

//err_exit.c
void	perr_exit(char *str);

//use_fd_safe.c
int		dup_s(int fd);
int		dup2_s(int fd1, int fd2);
int		close(fd);
int		open_s(char *path, int o_flag);


//use_dir_safe.c
int				chdir_s(const char *path);
int				closedir_s(DIR *dirp);
struct dirent	*readdir_s(DIR *dirp);

//use_heap_safe.c
void			*malloc_s(int size_of_container);

//use_write_getcwd_safe.c
char			*getcwd_s(char *buf, size_t size);
int				write_s(int fd, const char *str, int _strlen);

#endif