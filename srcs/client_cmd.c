/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 22:33:32 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/07 18:41:08 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	client_get(int sock, char *filename)
{
	(void)sock;
	(void)filename;
	ft_putendl("FIXME");
}

void	client_put(int sock, char *filename)
{
	int			fd;
	int			ret;
	char		buf[BUF_SIZE];
	struct stat	file_stat;

	/*
	file_size = server_recvint(cs);
	file_contents = malloc(file_size * sizeof(char));
	server_recvstr(cs, file_contents, file_size);
	if (ft_strchr(filename, ' ') != NULL)
		server_sendbuf(cs, "ERROR: Usage: put [file_path]");
	else if ((fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0777)) == -1)
		server_sendbuf(cs, "ERROR: file creation failed");
	else
	{
		if (write(fd, file_contents, file_size) == -1)
			server_sendbuf(cs, "ERROR: file write failed");
		else
			server_sendbuf(cs, "SUCCESS: file written to server");
		close(fd);
	}
	free(file_contents);
	*/
	// if (ft_strchr(filename, ' ') != NULL)
	// 	shell_pwarning(NULL, "Usage: put [file_path]")
	/* else */if ((fd = open(filename, O_RDONLY)) == -1)
		shell_pwarning(NULL, "file open failed");
	else
	{
		fstat(fd, &file_stat);
		server_sendint(sock, file_stat.st_size);
		while ((ret = read(fd, buf, BUF_SIZE)) > 0)
			send(sock, buf, ret, 0);
		close(fd);
		server_recvbuf(sock, buf);
		ft_putendl(buf);
	}
}

void	client_ls(int sock)
{
	int		size;
	char	*output;

	server_sendbuf(sock, "ls");
	size = server_recvint(sock);
	output = malloc(size * sizeof(char));
	server_recvstr(sock, output, size);
	output[size - 1] = '\n';
	write(1, output, size);
	free(output);
}
