/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sploadie_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 10:42:01 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/04/30 19:47:22 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	sploadie_env(t_args *args, t_env env)
{
	if (args->arg_count != 1)
		return ((void)shell_pwarning(args->args[0],
		": incorrect number of arguments (1)"));
	print_env(env);
}
