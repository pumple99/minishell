/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_libft_safe_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:05:09 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:13:12 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "safe_function_bonus.h"

char	*ft_strdup_s(const char *str)
{
	char	*re;

	re = ft_strdup(str);
	if (re == NULL)
		malloc_error();
	return (re);
}

char	*ft_substr_s(const char *str, unsigned int start, size_t len)
{
	char	*re;

	re = ft_substr(str, start, len);
	if (re == NULL)
		malloc_error();
	return (re);
}
