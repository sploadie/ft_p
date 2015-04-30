/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 11:15:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/24 11:51:19 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	read_stdin(t_env env, char **line)
{
	int	ret;

	*line = NULL;
	signal(SIGTSTP, handle_sigtstp);
	if ((ret = get_next_line(0, line)) && ft_strcmp(*line, "exit"))
		return ;
	if (!ret)
		write(1, "exit\n", 5);
	ft_putstr(GOODBYE);
	free(*line);
	chdir(fetch_key_val(env, "OLDPWD"));
	exit(0);
}
