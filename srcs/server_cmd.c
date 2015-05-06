/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:02:59 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/06 17:47:54 by tgauvrit         ###   ########.fr       */
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
	server_sendstr(cs, output);
	free(output);
}

void	server_mkdir(int cs, char *dirname)
{
	char	*message;

	if (ft_strchr(dirname, ' ') == NULL)
	{
		dirname -= 2;
		ft_strcpy(dirname, "./");
		if (mkdir(dirname, 0777) == 0)
			message = "SUCCESS: ";
		else
			message = "ERROR: ";
		message = ft_strjoin(message, dirname);
		server_sendstr(cs, message);
	}
	else
		server_sendstr(cs, "ERROR: Usage: mkdir [dirname]");
}

void	server_put(int cs, char *cmd)
{
	(void)cs;
	(void)cmd;
	server_sendstr(cs, "FIXME");
}

void	server_get(int cs, char *cmd)
{
	(void)cs;
	(void)cmd;
	server_sendstr(cs, "FIXME");
}

void	server_cd(int cs, char *cmd)
{
	(void)cs;
	(void)cmd;
	server_sendstr(cs, "FIXME");
}
