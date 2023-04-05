/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:39:29 by seunghoy          #+#    #+#             */
/*   Updated: 2023/04/05 19:09:45 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static void	init_state(t_state *state)
{
	state->char_s = 0;
	state->num_s = outside;
}

/*cmd: pipex command with options, never null
return: string array, last value of array is null*/
static t_token	**make_arr(char *input)
{
	t_state	state;
	t_state	new_state;
	int		str_count;
	t_token	*str_arr;

	state;
	str_count = 0;
	while (*input)
	{
		new_state = get_new_state(state, *(input++));
		if (state == 0 && new_state != 0)
			++str_count;
		state = new_state;
	}
	str_arr = (t_token *)malloc(sizeof(t_token) * (str_count + 1));
	if (str_arr)
		str_arr[str_count] = 0;
	return (str_arr);
}

/*src: word's starting address, not a start of total cmd input
return: size of string, not include " and '*/
static int	get_str_size(char *src)
{
	int		str_size;
	int		new_state;
	int		state;

	state = 0;
	str_size = 0;
	while (*src)
	{
		new_state = get_new_state(state, *(src++));
		if (new_state == 0)
			break ;
		if ((state == 0 && new_state == 1) || state == new_state || state > 3)
			str_size++;
		state = new_state;
	}
	return (str_size);
}

/*src: word's starting address, not a start of total cmd input
return: copied string, not include " and '*/
static char	*copy_str_in_cmd(char *src)
{
	int		state;
	int		new_state;
	int		str_size;
	int		str_idx;
	char	*copy_str;

	state = 0;
	str_idx = 0;
	str_size = get_str_size(src);
	copy_str = (char *)malloc(str_size + 1);
	if (copy_str == 0)
		return (0);
	copy_str[str_size] = '\0';
	while (*src)
	{
		new_state = get_new_state(state, *src);
		if (new_state == 0)
			break ;
		if ((state == 0 && new_state == 1) || state == new_state || state > 3)
			copy_str[str_idx++] = *src;
		state = new_state;
		++src;
	}
	return (copy_str);
}

/*cmd: pipex command with options, never null
return: parsed string array, 0 when error*/
char	**parse_cmd(char *cmd)
{
	char	**str_arr;
	int		state;
	int		new_state;
	int		arr_idx;

	str_arr = make_arr(cmd);
	if (str_arr == 0)
		return (0);
	state = 0;
	arr_idx = 0;
	while (*cmd)
	{
		new_state = get_new_state(state, *cmd);
		if (state == 0 && new_state != 0)
		{
			str_arr[arr_idx++] = copy_str_in_cmd(cmd);
			if (str_arr[arr_idx - 1] == 0)
				return (free_parse_arr(str_arr, arr_idx - 1));
		}
		state = new_state;
		++cmd;
	}
	return (str_arr);
}
