/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 17:00:21 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 11:17:10 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*key_key_str(char *env_str)
{
	char	*eql_ptr;

	if (!(eql_ptr = ft_strchr(env_str, '=')))
		shell_perror("Invalid variable in the [environ] standard C global");
	return (ft_strsub(env_str, 0, eql_ptr - env_str));
}

char	*key_val_str(char *env_str)
{
	char	*eql_ptr;

	if (!(eql_ptr = ft_strchr(env_str, '=')))
		shell_perror("Invalid variable in the [environ] standard C global");
	return (ft_strdup(eql_ptr + 1));
}
