/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:39:05 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/21 18:34:25 by seunghoy         ###   ########.fr       */
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

#endif