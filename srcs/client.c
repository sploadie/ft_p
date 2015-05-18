/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/18 20:46:56 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_client(int port, char *addr, char *buf)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		shell_perror("getprotobyname(\"tcp\") returned 0");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)))
		shell_perror("can't assign requested address");
	signal(SIGTSTP, handle_signals);
	signal(SIGPIPE, handle_signals);
	signal(SIGINT, handle_signals);
	handle_signals(sock);
	server_recvbuf(sock, buf);
	ft_putendl(buf);
	return (sock);
}

void	client_do(int sock, char *buf)
{
	if (ft_strequ(buf, "help"))
		ft_putstr(HELP);
	else if (ft_strequ(buf, "ls"))
		client_ls(sock);
	else if (ft_strncmp(buf, "get ", 4) == 0)
		client_get(sock, buf);
	else if (ft_strncmp(buf, "put ", 4) == 0)
		client_put(sock, buf);
	else
	{
		server_sendbuf(sock, buf);
		server_recvbuf(sock, buf);
		ft_putendl(buf);
	}
}

void	client(int sock, char *path, char *buf)
{
	int		ret;

	ft_putfourstr(WELCOME, path, " ", PROMPT);
	while (ret = read(0, buf, BUF_SIZE), ret > 0)
	{
		if (ret == BUF_SIZE)
			shell_pwarning(NULL, "command too long");
		else
		{
			buf[ret - 1] = '\0';
			if (ft_strequ(buf, "quit"))
				break ;
			client_do(sock, buf);
		}
		ft_putfourstr(path, " ", PROMPT, NULL);
	}
	server_sendbuf(sock, "quit");
	ft_putstr(GOODBYE);
	exit(0);
}

int		main(int argc, char **argv)
{
	int		sock;
	char	buf[BUF_SIZE + 1];

	buf[BUF_SIZE] = '\0';
	if (argc != 3)
		shell_perror("USAGE: ./client [machine] [port]");
	sock = create_client(ft_atoi(argv[2]), argv[1], buf);
	argv[1][ft_strlen(argv[1])] = ':';
	client(sock, argv[1], buf);
	return (0);
}
