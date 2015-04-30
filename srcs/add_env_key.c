/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 16:56:39 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/20 17:42:17 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** NEOKEY should NOT be allocated.
** NEOVAL should     be allocated.
*/

void	add_env_key(t_env env, char *neokey, char *neoval)
{
	if (!neoval)
		neoval = ft_strdup("");
	if (!*env)
		*env = gen_env_key(ft_strdup(neokey), neoval, NULL);
	else if (!ft_strcmp((*env)->key, neokey))
	{
		free((*env)->val);
		(*env)->val = neoval;
	}
	else if (ft_strcmp((*env)->key, neokey) > 0)
		*env = gen_env_key(ft_strdup(neokey), neoval, *env);
	else if (!(*env)->next)
		(*env)->next = gen_env_key(ft_strdup(neokey), neoval, NULL);
	else if (ft_strcmp((*env)->next->key, neokey) > 0)
		(*env)->next = gen_env_key(ft_strdup(neokey), neoval, (*env)->next);
	else
		add_env_key(&((*env)->next), neokey, neoval);
}
