/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:02:59 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/18 17:50:21 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	server_ls(int cs)
{
	char			path[BUF_SIZE];
	char			*output;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(getcwd(path, BUF_SIZE));
	output = ft_strdup("SUCCESS:");
	while (ft_strjoinfree(&output, "\n"), entry = readdir(dir), entry != NULL)
		ft_strjoinfree(&output, entry->d_name);
	closedir(dir);
	server_sendint(cs, ft_strlen(output) + 1); //Send size of output first
	server_sendstr(cs, output, ft_strlen(output) + 1);
	free(output);
}

void	server_mkdir(int cs, char *dirname)
{
	char	*message;

	if (ft_strchr(dirname, ' ') == NULL)
	{
		if (mkdir(dirname, 0777) == 0)
			message = "SUCCESS: created directory ";
		else
			message = "ERROR: failed to create directory ";
		message = ft_strjoin(message, dirname);
		server_sendbuf(cs, message);
		free(message);
	}
	else
		server_sendbuf(cs, "ERROR: Usage: mkdir [dirname]");
}

void	server_put(int cs, char *filename)
{
	int		file_size;
	char	*file_contents;
	int		fd;

	file_size = server_recvint(cs);
	file_contents = malloc(file_size * sizeof(char));
	server_recvstr(cs, file_contents, file_size);
	if (ft_strrchr(filename, '/') != NULL)
		filename = ft_strrchr(filename, '/') + 1;
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0777)) == -1)
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
}

void	server_get(int cs, char *filename)
{
	int			fd;
	int			ret;
	char		buf[BUF_SIZE];
	struct stat	file_stat;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		server_sendint(cs, -1);
		server_sendbuf(cs, "ERROR: file open failed");
	}
	else
	{
		fstat(fd, &file_stat);
		server_sendint(cs, file_stat.st_size);
		while ((ret = read(fd, buf, BUF_SIZE)) > 0)
			send(cs, buf, ret, 0);
		close(fd);
		server_sendbuf(cs, "SUCCESS: file read from server");
	}
}

void	server_cd(int cs, char *path)
{
	char	buf[BUF_SIZE];
	size_t	len;
	size_t	root_len;

	if (chdir(path) == -1)
	{
		server_sendbuf(cs, "ERROR: invalid path");
		return ;
	}
	len = ft_strlen(getcwd(buf, BUF_SIZE));
	root_len = ft_strlen(server_root_dir());
	if (len < root_len || ft_strncmp(buf, server_root_dir(), root_len) != 0)
		chdir(server_root_dir());
	server_pwd(cs);
}




















