/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 18:06:15 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/27 13:36:26 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_spill	*get_spill(int const fd)
{
	static t_spill	*first_spill = NULL;
	t_spill			*curr_spill;

	curr_spill = first_spill;
	while (curr_spill)
	{
		if (curr_spill->fd == fd)
			return (curr_spill);
		curr_spill = curr_spill->next;
	}
	curr_spill = (t_spill*)malloc(sizeof(t_spill));
	if (!curr_spill)
		return (NULL);
	curr_spill->fd = fd;
	curr_spill->text = (char*)malloc(sizeof(char));
	if (!curr_spill->text)
		return (NULL);
	*(curr_spill->text) = '\0';
	curr_spill->next = first_spill;
	first_spill = curr_spill;
	return (curr_spill);
}

static int		scoop_spill(t_spill *spill,
							char *spill_text, char **line, char *cutoff)
{
	char	*to_free;

	if (!cutoff)
	{
		*line = spill_text;
		if (!(spill->text = ft_strnew(0)))
			return (0);
		return (1);
	}
	*line = ft_strsub(spill_text, 0, (int)(cutoff - spill_text));
	if (!*line)
		return (0);
	to_free = spill->text;
	spill->text = ft_strdup(cutoff + 1);
	if (!spill->text)
		return (0);
	free(to_free);
	return (1);
}

static int		read_spill(t_spill *spill, char **line)
{
	char	*line_end;

	if ((line_end = ft_strchr(spill->text, '\n')))
	{
		if (!scoop_spill(spill, spill->text, line, line_end))
			return (-1);
		return (1);
	}
	return (0);
}

static int		read_to_spill(int const fd, t_spill *spill, char **line)
{
	int				ret;
	int				spill_ret;
	char			buf[BUF_SIZE + 1];

	spill_ret = read_spill(spill, line);
	if (spill_ret == -1 || spill_ret == 1)
		return (spill_ret);
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		*line = spill->text;
		spill->text = ft_strjoin(spill->text, buf);
		free(*line);
		spill_ret = read_spill(spill, line);
		if (spill_ret == -1 || spill_ret == 1)
			return (spill_ret);
	}
	if (ret != 0)
		return (-1);
	scoop_spill(spill, spill->text, line, NULL);
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	t_spill	*spill;

	if (!line || BUF_SIZE < 1)
		return (-1);
	spill = get_spill(fd);
	if (!spill)
		return (-1);
	return (read_to_spill(fd, spill, line));
}
