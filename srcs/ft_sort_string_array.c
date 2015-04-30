/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:54:12 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/17 14:59:48 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int	get_null_term_size(char **ptr)
{
	int	size;

	size = 0;
	while (*ptr)
	{
		ptr++;
		size++;
	}
	return (size);
}

void		ft_sort_string_array(char **string_array, int size)
{
	int		i;
	int		j;
	char	*temp;

	if (size == -1)
		size = get_null_term_size(string_array);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(string_array[j], string_array[j + 1]) > 0)
			{
				temp = string_array[j];
				string_array[j] = string_array[j + 1];
				string_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
