/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sindong-yeob <sindong-yeob@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:35:22 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/26 18:20:49 by sindong-yeo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int		get_index(char *str)
{
	char	region;
	int		index;

	region = str[0] - 'A';
	if (0 <= region && region <= 26)
		index = region;
	else if (region == 31)
		index = 52;
	else if (region == -2)
		index = 53;
	else if (region == -32)
		index = 54;
	else
		index = str[0] - 'a' + 26;
	return (index);
}
