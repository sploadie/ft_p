/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 14:36:57 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 16:01:49 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int	end_in_quotes(char *str)
{
	int	in_quotes;

	in_quotes = -1;
	while (*str)
	{
		if (*str == '\"')
			in_quotes *= -1;
		str++;
	}
	if (in_quotes > 0)
		return (1);
	return (0);
}

int			arg_count_check(int arg_count)
{
	if (arg_count >= INPUT_MAX_ARGS)
		shell_perror("Maximum arguments surpassed");
	return (arg_count);
}

static char	*clip_arg(char *str, char **next)
{
	char	*start;
	char	*curr;
	int		in_quotes;

	if (!(start = str))
		return (NULL);
	curr = str;
	in_quotes = -1;
	while (*curr)
	{
		while (*str == '\"' && (in_quotes *= -1))
			str++;
		if (!*str || (in_quotes == -1 && ft_strchr(ESCAPE_CHARS, *str)))
		{
			if (*str)
				str++;
			*curr = '\0';
		}
		else
			*(curr++) = *(str++);
	}
	while (*str && ft_strchr(ESCAPE_CHARS, *str))
		str++;
	*next = (*str ? str : NULL);
	return (start);
}

t_args		*parse_input_args(t_env env, char *str, int isalloc)
{
	t_args	*neoargs;
	char	*arg_ptrs[INPUT_MAX_ARGS];
	int		arg_count;

	if (!isalloc)
		str = ft_strdup(str);
	if (end_in_quotes(str))
		return (parse_input_args(env, append_quote(env, str), 1));
	neoargs = check_malloc(ft_memalloc(sizeof(t_args)));
	neoargs->str = str;
	str = ft_strdup(str);
	arg_count = 0;
	arg_ptrs[0] = clip_arg(str, &str);
	while (arg_ptrs[arg_count])
		arg_ptrs[arg_count_check(++arg_count)] = clip_arg(str, &str);
	neoargs->args = ft_memdup(arg_ptrs, sizeof(char *) * (arg_count + 1));
	neoargs->arg_count = arg_count;
	free(str);
	return (neoargs);
}
