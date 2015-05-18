/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 14:03:53 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/18 17:48:09 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	handle_signals(int signum)
{
	static int	sock = -1;

	if (sock == -1)
	{
		sock = signum;
		return ;
	}
	if (sock == 0)// Server
		shell_perror("Server encountered an issue. Need a tissue?");
	server_sendbuf(sock, "quit");
	write(1, "\n", 1);
	shell_pwarning("", "Server connection ended");
	ft_putstr(GOODBYE);
	exit(0);
}
