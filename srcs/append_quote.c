/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:29:08 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 11:04:26 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*append_quote(t_env env, char *str)
{
	char	*str_add;

	str_add = NULL;
	ft_putstr(QUOTE_PROMPT);
	read_stdin(env, &str_add);
	ft_strjoinfree(&str, "\n");
	ft_strjoinfree(&str, str_add);
	free(str_add);
	return (str);
}
