/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:57:12 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/07 22:25:28 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parse.h"

typedef struct s_fds
{
	int	left[2];
	int	right[2];
}	t_fds;

typedef enum e_builtin_num
{
	cd = 33,
	echo,
	env,
	__exit,
	export,
	pwd,
	unset = 39
}			t_builtin_num;

typedef struct s_fd_node
{
	int					fd;
	struct s_fd_node	*next;
}	t_fd_node;

typedef struct s_fd_list
{
	t_fd_node	*first_node;
	int			err;
}	t_fd_list;

//execute.c
int			execute(t_token_list *tl, t_admin *hash_map, char ***envp);

//execute_utils.c
void		save_stdio(int *stdio_fds);
void		restore_stdio(int *stdio_fds);
int			is_redirection(t_token *token);
int			is_and_or_pipe_end(t_token *token);
int			is_or_and_end(t_token *token);

//execute_pipe.c
int			execute_pipe(t_admin *hash_map, char ***envp, t_token *token);

//execute_minimal.c
int			execute_minimal(t_admin *hash_map, char ***envp, \
t_token *token, int is_pipe);

//execute_minimal_utils.c
char		*has_paren(t_token *token);
int			is_builtin(char *minimal_cmd);

//execute_redirection.c
t_fd_list	execute_redirection(t_token *token);
int			close_redirect_fds(t_fd_list fd_list, int re);

//execute_cmd.c
int			execute_builtin_cmd(t_admin *hash_map, char ***envp, \
char **minimal_cmd, int builtin_num);
int			execute_non_builtin_cmd(t_admin *hash_map, char ***envp, \
char **minimal_cmd, int is_pipe);

//execute_cmd_utils.c
char		**get_path_list_from_env_path(t_admin *hash_map);
void		is_executable(char *cmd_with_path);
char		*get_path(char **path_list, char *cmd);
char		*find_path(char **path_list, char *cmd);

//execute_subshell.c
int			execute_subshell(t_admin *hash_map, char *involve_paren_str, \
char ***envp, int is_pipe);

//execute_heredoc.c
int			execute_heredoc(t_admin *hash_map, t_token_list *tl);

//execute_heredoc_utils.c
char		*get_quote_removal_limiter(char *unremoved);
void		write_in_file(t_admin *hash_map, \
int fd, char *line, int have_to_expand);

//wait.c
int			wait_last_child(t_admin *hash_map, pid_t last_child_pid, \
int child_cnt);
void		set_questionmark(t_admin *hash_map, int exit_status);

//set_questionmark.c
void		set_questionmark(t_admin *hash_map, int exit_status);

#endif
