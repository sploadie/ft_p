/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/06 17:35:55 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (proto = getprotobyname("tcp"), (proto) == 0)
		shell_perror("getprotobyname(\"tcp\") returned 0");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (struct sockaddr *)&sin, sizeof(sin));
	listen(sock, 1);
	printf("Server started at address %d port %d\n", INADDR_ANY, port);
	return (sock);
}

int		server_do(int cs, char *cmd)
{
	if (ft_strcmp(cmd, "quit") == 0)
	{
		printf("Client %d disconnected\n", cs);
		close(cs);
		exit(0);
	}
	else if (ft_strcmp(cmd, "ls") == 0)
		server_ls(cs);
	else if (ft_strcmp(cmd, "pwd") == 0)
		server_sendstr(cs, server_pwd());
	else if (ft_strncmp(cmd, "mkdir ", 6) == 0)
		server_mkdir(cs, cmd + 6);
	else if (ft_strncmp(cmd, "put ", 4) == 0)
		server_put(cs, cmd + 4);
	else if (ft_strncmp(cmd, "get ", 4) == 0)
		server_get(cs, cmd + 4);
	else if (ft_strncmp(cmd, "cd ", 3) == 0)
		server_cd(cs, cmd + 3);
	else
		server_sendstr(cs, "ERROR: Incorrect command");
	return (0);
}

void	handle_child(int cs, unsigned short sin_port)
{
	int					ret;
	char				buf[BUF_SIZE + 1];

	buf[BUF_SIZE] = '\0';
	server_sendstr(cs, "SUCCESS: Welcome to sploadieFT_P");
	server_pwd();
	while (1)
	{
		ret = recv(cs, buf, BUF_SIZE, MSG_WAITALL);
		printf("%u: [%s]\n", sin_port, buf);
		server_do(cs , buf);
	}
	close(cs);
	exit(0);
}

void	server(int sock)
{
	int					pid;
	int					cs;
	struct sockaddr_in	csin;
	unsigned int		cslen;

	while (1)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		printf("Client connected:\nsin_family: %i\nsin_port: %u\nsin_addr: %s\n", csin.sin_family, csin.sin_port, inet_ntoa(csin.sin_addr));//.s_addr));
		if (pid = fork(), pid == 0)
			handle_child(cs, csin.sin_port);
		close(cs);//Parent closes their copy of the socket. Probably.
	}
}

int		main(int argc, char **argv)
{
	int	port;
	int	sock;

	if (argc != 2)
		shell_perror("USAGE: ./serveur [port]");
	sock = create_server(ft_atoi(argv[1]));//argv[1] is port
	server(sock);
	close(sock);
	return (0);
}
