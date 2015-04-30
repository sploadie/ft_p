/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/17 14:34:03 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filedir.h"

void		get_file_link(t_filedir *filedir)
{
	char	str[10000];
	int		link_len;

	link_len = readlink(filedir->path, str, 9999);
	if (link_len == -1)
	{
		filedir->link = NULL;
		return ;
	}
	str[link_len] = '\0';
	filedir->link = check_malloc(ft_strdup(str));
}

static void	tru_arg(char *arg)
{
	if (*arg == '\0')
	{
		ft_putendl_fd("fts_open: No such file or directory", 2);
		exit(1);
	}
}

static void	filedir_error(char *path)
{
	ft_putendl_fd("Filedir: stat and lstat failed for path \"", 2);
	if (path)
		ft_putendl_fd(path, 2);
	else
		ft_putendl_fd("(NULL)", 2);
	ft_putendl_fd("\"\n", 2);
}

t_filedir	*filedir(char *input_path)
{
	t_filedir	*neofiledir;

	tru_arg(input_path);
	neofiledir = check_malloc(malloc(sizeof(t_filedir) * 2));
	neofiledir->path = check_malloc(ft_strdup(input_path));
	if (ft_strchr(neofiledir->path, '/'))
	{
		neofiledir->name = ft_strrchr(neofiledir->path, '/') + 1;
	}
	else
	{
		neofiledir->name = neofiledir->path;
	}
	neofiledir->name_len = ft_strlen(neofiledir->name);
	neofiledir->stats = check_malloc(malloc(sizeof(struct stat)));
	if (lstat(neofiledir->path, neofiledir->stats) == -1 &&
		stat(neofiledir->path, neofiledir->stats) == -1)
	{
		filedir_error(neofiledir->path);
		neofiledir->link = NULL;
		del_filedir(neofiledir);
		return (NULL);
	}
	get_file_link(neofiledir);
	return (neofiledir);
}

t_filedir	*direct_filedir(char *input_path)
{
	t_filedir	*neofiledir;

	tru_arg(input_path);
	neofiledir = check_malloc(malloc(sizeof(t_filedir) * 2));
	neofiledir->path = check_malloc(ft_strdup(input_path));
	neofiledir->name = neofiledir->path;
	neofiledir->name_len = ft_strlen(neofiledir->name);
	neofiledir->stats = check_malloc(malloc(sizeof(struct stat)));
	if (lstat(neofiledir->path, neofiledir->stats) == -1 &&
		stat(neofiledir->path, neofiledir->stats) == -1)
	{
		filedir_error(neofiledir->path);
		neofiledir->link = NULL;
		del_filedir(neofiledir);
		return (NULL);
	}
	get_file_link(neofiledir);
	return (neofiledir);
}
