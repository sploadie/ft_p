/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfourstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 14:04:54 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/21 16:40:27 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putfourstr(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		ft_putstr(s1);
	if (s2)
		ft_putstr(s2);
	if (s3)
		ft_putstr(s3);
	if (s4)
		ft_putstr(s4);
}
