/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 16:32:10 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/05 22:39:29 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define GNL_BUF_SIZE 65

typedef struct			s_spill
{
	char				*text;
	int					fd;
	struct s_spill		*next;
}						t_spill;

int						get_next_line(int const fd, char **line);

#endif
