/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:25:41 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/07 15:44:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*server_root_dir(void)
{
	static char	*pwd = NULL;

	if (pwd == NULL)
		pwd = getcwd(malloc(BUF_SIZE), BUF_SIZE);
	return (pwd);
}

void	server_pwd(int cs)
{
	char	buf[BUF_SIZE];
	char	*path;

	getcwd(buf, BUF_SIZE);
	path = ft_strjoin("SUCCESS: ", buf + ft_strlen(server_root_dir()));
	ft_strjoinfree(&path, "/");
	server_sendbuf(cs, path);
	free(path);
}
