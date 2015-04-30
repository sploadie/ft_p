/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_env_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 11:53:04 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 11:53:22 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

t_env_key	*fetch_env_key(t_env env, char *key_str)
{
	if (!*env)
		return (NULL);
	if (!ft_strcmp((*env)->key, key_str))
		return (*env);
	if (ft_strcmp((*env)->key, key_str) < 0)
		return (fetch_env_key(&((*env)->next), key_str));
	return (NULL);
}

char		*fetch_key_val(t_env env, char *key_str)
{
	t_env_key	*key;

	if ((key = fetch_env_key(env, key_str)))
		return (key->val);
	return (NULL);
}
