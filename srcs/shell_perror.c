/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_perror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:54:12 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/07 12:18:47 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	shell_perror(char *str)
{
	ft_putstr_fd(RET_PROMPT, 2);
	ft_putstr_fd("ERROR: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd("(Error not provided)", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	*shell_pwarning(char *s1, char *s2)
{
	ft_putstr_fd(RET_PROMPT, 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	else
		ft_putstr_fd("WARNING: ", 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	else
		ft_putstr_fd("(Warning not provided)", 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

void	shell_psignal(char *s1, int signum, char *s2, char *signame)
{
	ft_putstr_fd(RET_PROMPT, 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	else
		ft_putstr_fd("Signal ", 2);
	ft_putnbr_fd(signum, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	else
		ft_putstr_fd(" ended your process.", 2);
	if (signame)
		ft_putstr_fd(signame, 2);
	ft_putstr_fd("\n", 2);
}
