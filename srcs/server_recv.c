/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_recv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 13:53:11 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/07 15:34:40 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		server_recvstr(int sock, char *buf, size_t length)
{
	int		ret;

	ret = recv(sock, buf, length, MSG_WAITALL);
	if ((size_t)ret < length)
		handle_signals(0);
	return (ret);
}

int		server_recvbuf(int sock, char *buf)
{
	return (server_recvstr(sock, buf, BUF_SIZE));
}

int		server_recvint(int sock)
{
	int		num;

	server_recvstr(sock, (char *)&num, sizeof(int));
	return (num);
}
