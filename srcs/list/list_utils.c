/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:35:22 by dongyshi          #+#    #+#             */
/*   Updated: 2023/04/06 19:09:23 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int		get_index(char *str) // hash_map의 몇번째 인덱스 리스트에 추가할지 정하기.
{
	char	region;
	int		index;

	region = str[0] - 'A';
	if (0 <= region && region <= 26)
		index = region;
	else if (region == 31)
		index = 53;
	else
		index = str[0] - 'a' + 26;
	return (index);
}
