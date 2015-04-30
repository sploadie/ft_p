/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_filedir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 14:20:11 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/17 13:53:34 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedir.h"

void	del_filedir(t_filedir *filedir)
{
	free(filedir->path);
	if (filedir->stats)
		free(filedir->stats);
	if (filedir->link)
		free(filedir->link);
	free(filedir);
}
