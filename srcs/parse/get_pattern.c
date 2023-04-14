/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoy <seunghoy@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:26:24 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/14 21:42:40 by seunghoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "list.h"
// #include "libft.h"

// #include <stdio.h>

// void	get_pattern(/*t_admin *pattern_list, */int path_len, char *wild_card_str)
// {
// 	int	start_idx;
// 	int	end_idx;

// 	start_idx = path_len;
// 	end_idx = start_idx;
// 	while (1)
// 	{
// 		if (wild_card_str[end_idx] == '/')
// 		{
// 			printf("%s\n", ft_substr(wild_card_str, start_idx, end_idx - start_idx + 1));
// 			start_idx = end_idx + 1;
// 		}
// 		else if (wild_card_str[end_idx] == 0)
// 		{
// 			printf("%s\n", ft_substr(wild_card_str, start_idx, end_idx - start_idx + 1));
// 			break ;
// 		}
// 		++end_idx;
// 	}
// }

// int	main()
// {
// 	get_pattern(0, "ZZ*a*d/KKK*/llll*lll");
// 	return (0);
// }