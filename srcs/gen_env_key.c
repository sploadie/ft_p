/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 16:56:19 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/17 16:57:49 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

t_env_key	*gen_env_key(char *key, char *val, t_env_key *next)
{
	t_env_key	*neokey;

	neokey = check_malloc(malloc(sizeof(t_env_key)));
	neokey->key = key;
	neokey->val = val;
	neokey->next = next;
	return (neokey);
}
