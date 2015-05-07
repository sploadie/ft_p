/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:14:19 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/07 17:07:52 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	server_sendstr(int sock, char *str, size_t size)
{
	char	buf[size];

	if (ft_strlen(str) >= size)
		shell_perror("server_sendstr: message too long");
	ft_strncpy(buf, str, size);
	send(sock, buf, size, 0);
}

void	server_sendbuf(int sock, char *str)
{
	server_sendstr(sock, str, BUF_SIZE);
}

void	server_sendint(int sock, int num)
{
	send(sock, &num, sizeof(int), 0);
}
