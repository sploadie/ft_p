/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:25:41 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/05 18:17:46 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*server_pwd(void)
{
	static char	*pwd = NULL;

	if (pwd == NULL)
		pwd = getcwd(malloc(1024), 1024);
	return (pwd);
}
