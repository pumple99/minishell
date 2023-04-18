/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:04:31 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/18 20:46:31 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/parse.h"
#include "../libft/libft.h"

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
	char	file_num_str[11];
	char	*joined_filename;

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
	if (ft_strncmp(limiter, line, len) != 0)
		return (0);
	else if (line[len] == '\n')
		return (1);
	return (0);
}

static void	read_heredoc(char *filename, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// check_open_fd(HEREDOC_TEMP, fd);
	while (1)
	{
		write(1, "> ", 2);
		// line = check_gnl(get_next_line(0));
		if (line == 0 || is_same_with_limiter(limiter, line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	// check_close(fd);
}

void	execute_heredoc(t_token_list *tl)
{
	t_token	*token;
	char	*heredoc_filename;

	token = tl->head;
	while (token->type != end)
	{
		if (token->type == heredoc)
		{
			heredoc_filename = get_heredoc_filename();
			read_heredoc(heredoc_filename, token->next->string);
			free(token->string);
			token->string = (char *)malloc(2);
			(token->string)[0] = '<';
			(token->string)[1] = 0;
			token = token->next;
			free(token->string);
			token->string = heredoc_filename;
		}
		token = token->next;
	}	
}