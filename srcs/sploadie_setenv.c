/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sploadie_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 10:26:50 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 16:59:55 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	sploadie_setenv(t_args *args, t_env env)
{
	if (args->arg_count == 2)
	{
		if (!(args->args[2] = ft_strchr(args->args[1], '='))
			|| args->args[2] + 1 == '\0')
			return ((void)shell_pwarning(args->args[1],
			": not a valid environment key-value pair"));
		*(args->args[2]++) = '\0';
	}
	else if (args->arg_count != 3)
		return ((void)shell_pwarning(args->args[0],
		": incorrect number of arguments (2)"));
	add_env_key(env, args->args[1], ft_strdup(args->args[2]));
	if (args->arg_count == 2)
		args->args[2] = NULL;
}
