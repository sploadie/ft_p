/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 16:57:05 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 11:23:57 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void	free_key(t_env_key **dead_key)
{
	t_env_key	*temp_key;

	temp_key = *dead_key;
	*dead_key = (*dead_key)->next;
	free(temp_key->key);
	free(temp_key->val);
	free(temp_key);
}

int			del_env_key(t_env env, char *del_key)
{
	if (!*env)
		return (0);
	else if (!ft_strcmp((*env)->key, del_key))
	{
		free_key(env);
		return (1);
	}
	else if (ft_strcmp((*env)->key, del_key) < 0)
		return (del_env_key(&((*env)->next), del_key));
	return (0);
}
