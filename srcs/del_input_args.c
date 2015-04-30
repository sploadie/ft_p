/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_input_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 16:16:43 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/21 16:26:57 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** Sets args to NULL to avoid accidents
** args->str IS FREED, so no need to free it elsewhere
*/

void	del_input_args(t_args **args)
{
	free((*args)->str);
	free((*args)->args);
	free(*args);
	*args = NULL;
}
