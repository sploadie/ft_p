/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:12:51 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/17 14:28:35 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDIR_H
# define FILEDIR_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>

# include "libft.h"

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

typedef struct			s_filedir
{
	char				*name;
	size_t				name_len;
	char				*path;
	t_stat				*stats;
	char				*link;
}						t_filedir;

void					*check_malloc(void *ret);
t_filedir				*filedir(char *name);
t_filedir				*direct_filedir(char *input_path);
void					del_filedir(t_filedir *filedir);

#endif
