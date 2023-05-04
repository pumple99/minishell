/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:04:31 by seunghoy          #+#    #+#             */
/*   Updated: 2023/05/04 21:13:26 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include "parse.h"
#include "libft.h"
#include "execute.h"
#include "safe_function.h"

#define HEREDOC_BASENAME ".heredoc_temp_file_"
#define FILE_NUM_STEP 65537

static void	fill_file_num_str(char *file_num_str, unsigned int file_num)
{
	int		idx;
	int		swap_idx;
	char	temp;

	idx = 0;
	while (file_num > 0)
	{
		file_num_str[idx++] = "0123456789"[file_num % 10];
		file_num /= 10;
	}
	file_num_str[idx] = 0;
	swap_idx = -1;
	while (++swap_idx < idx / 2)
	{
		temp = file_num_str[swap_idx];
		file_num_str[swap_idx] = file_num_str[idx - swap_idx - 1];
		file_num_str[idx - swap_idx - 1] = temp;
	}
}

static char	*get_heredoc_filename(void)
{
	static unsigned int	heredoc_file_num;
	char				file_num_str[11];
	char				*joined_filename;

	while (1)
	{
		fill_file_num_str(file_num_str, heredoc_file_num);
		joined_filename = ft_strjoin(HEREDOC_BASENAME, file_num_str);
		if (joined_filename == 0)
			return (0);
		if (access(joined_filename, F_OK) != 0)
			return (heredoc_file_num += 1, joined_filename);
		free(joined_filename);
		heredoc_file_num += FILE_NUM_STEP;
	}
	return (0);
}

static int	is_same_with_limiter(char *limiter, char *line)
{
	size_t	len;

	len = ft_strlen(limiter);
	if (ft_strncmp(limiter, line, len + 1) == 0)
		return (1);
	return (0);
}

static int	read_heredoc(t_admin *hash_map, char *filename, char *limiter)
{
	int		fd;
	int		have_to_expand;
	char	*line;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork_s();
	if (pid == 0)
	{
		have_to_expand = !is_include_quote(limiter);
		limiter = get_quote_removal_limiter(limiter);
		signal(SIGINT, SIG_DFL);
		fd = open_s(filename, O_WRONLY | O_CREAT | O_TRUNC);
		if (fd == -1)
			exit (1);
		while (1)
		{
			line = readline("> ");
			if (line == 0 || is_same_with_limiter(limiter, line))
				exit (0);
			write_in_file(hash_map, fd, line, have_to_expand);
			free(line);
		}
	}
	return (wait_last_child(hash_map, pid, 1));
}

int	execute_heredoc(t_admin *hash_map, t_token_list *tl)
{
	t_token	*token;
	char	*heredoc_filename;
	int		heredoc_stat;

	token = tl->head;
	while (token->type != end)
	{
		if (token->type == heredoc)
		{
			heredoc_filename = get_heredoc_filename();
			heredoc_stat = read_heredoc(hash_map, \
					heredoc_filename, token->next->string);
			free(token->string);
			token->string = (char *)malloc_s(2);
			(token->string)[0] = '<';
			(token->string)[1] = 0;
			token = token->next;
			free(token->string);
			token->string = heredoc_filename;
			if (heredoc_stat != 0)
				return (1);
		}
		token = token->next;
	}
	return (0);
}
