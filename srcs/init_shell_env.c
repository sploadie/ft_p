/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 15:56:40 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 16:31:00 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static t_env_key	*parse_env_key(char **env_ptr)
{
	if (*env_ptr == NULL)
		return (NULL);
	return (gen_env_key(key_key_str(*env_ptr),
	key_val_str(*env_ptr), parse_env_key(env_ptr + 1)));
}

t_env				init_shell_env(char **environ)
{
	t_env		neoenv;
	t_env_key	*first_key;
	char		*str;

	ft_sort_string_array(environ, -1);
	first_key = parse_env_key(environ);
	neoenv = ft_memdup(&first_key, sizeof(t_env_key *));
	add_env_key(neoenv, "OLDPWD", getcwd(NULL, 0));
	add_env_key(neoenv, "PWD", getcwd(NULL, 0));
	if ((str = fetch_key_val(neoenv, "SHLVL")))
		add_env_key(neoenv, "SHLVL", ft_itoa(ft_atoi(str) + 1));
	return (neoenv);
}
