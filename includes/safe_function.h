/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:39:05 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:16:59 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_FUNCTION_H
# define SAFE_FUNCTION_H

# include <dirent.h>
# include <unistd.h>

//err_exit.c
void			perr_exit(char *str);
void			malloc_error(void);

//use_fd_safe.c
int				dup_s(int fd);
int				dup2_s(int fd1, int fd2);
int				close_s(int fd);
int				open_s(char *path, int o_flag);

//use_dir_safe.c
int				chdir_s(const char *path);
int				closedir_s(DIR *dirp);
struct dirent	*readdir_s(DIR *dirp);

//use_heap_safe.c
void			*malloc_s(int size_of_container);

//use_write_getcwd_safe.c
char			*getcwd_s(char *buf, size_t size);
int				write_s(int fd, const char *str, int _strlen);

//use_process_safe.c
int				pipe_s(int *fildes);
pid_t			fork_s(void);
int				execve_s(const char *path, char *const argv[], \
							char *const envp[]);

//use_file_safe.c
int				unlink_s(char *path);

//use_libft_safe.c
char			*ft_strdup_s(const char *str);
char			*ft_substr_s(const char *str, unsigned int start, size_t len);

#endif
