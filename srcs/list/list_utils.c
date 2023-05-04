/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyshi <dongyshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:35:22 by dongyshi          #+#    #+#             */
/*   Updated: 2023/05/04 21:13:49 by dongyshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_index(char *str)
{
	char	f_word;
	int		index;

	f_word = str[0];
	if (65 <= f_word && f_word <= 90)
		index = f_word - 'A';
	else if (97 <= f_word && f_word <= 122)
		index = f_word - 'a' + 26;
	else if (f_word == '_')
		index = 52;
	else if (f_word == '?')
		index = 53;
	else if (f_word == '!')
		index = 54;
	else
		return (-1);
	return (index);
}
