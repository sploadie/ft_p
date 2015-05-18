/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 22:33:32 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/18 17:47:44 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	client_get(int sock, char *cmd)
{
	int		f_size;
	char	*file_contents;
	int		fd;
	char	*filename;
	char	buf[BUF_SIZE];

	filename = cmd + 4;
	if (ft_strrchr(filename, '/') != NULL)
		filename = ft_strrchr(filename, '/') + 1;
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0777)) == -1)
		shell_pwarning(NULL, "file creation failed");
	else if (server_sendbuf(sock, cmd), (f_size = server_recvint(sock)) != -1)
	{
		file_contents = malloc(f_size * sizeof(char));
		server_recvstr(sock, file_contents, f_size);
		if (write(fd, file_contents, f_size) == -1)
			shell_pwarning("ERROR: ", "file write failed");
		else
			shell_pwarning("SUCCESS: ", "file written from server");
		free(file_contents);
		server_recvbuf(sock, buf);
		ft_putendl(buf);
	}
	close(fd);
}

void	client_put(int sock, char *cmd)
{
	int			fd;
	int			ret;
	char		buf[BUF_SIZE];
	struct stat	file_stat;

	if ((fd = open(cmd + 4, O_RDONLY)) == -1)
		shell_pwarning(NULL, "file open failed");
	else
	{
		server_sendbuf(sock, cmd);
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
