/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sendstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:14:19 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/06 16:16:08 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	server_sendstr(int sock, char *str)
{
	char	buf[BUF_SIZE];

	if (ft_strlen(str) >= BUF_SIZE)
		shell_perror("server_sendstr: message too long");
	ft_strncpy(buf, str, BUF_SIZE);
	send(sock, buf, BUF_SIZE, 0);
}
