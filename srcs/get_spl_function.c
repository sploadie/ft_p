/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spl_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 09:58:15 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 10:46:50 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

t_spl_func	*get_spl_function(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (&sploadie_cd);
	if (!ft_strcmp(str, "setenv"))
		return (&sploadie_setenv);
	if (!ft_strcmp(str, "unsetenv"))
		return (&sploadie_unsetenv);
	if (!ft_strcmp(str, "env"))
		return (&sploadie_env);
	return (NULL);
}
