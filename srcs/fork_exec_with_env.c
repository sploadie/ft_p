/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec_with_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 14:30:19 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 12:07:59 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** fork_exec_with_env:
** Last return is for norminette and flags
*/

size_t	env_key_str_len(t_env env)
{
	size_t	size;

	if (!*env)
		return (0);
	size = 2;
	size += ft_strlen((*env)->key);
	size += ft_strlen((*env)->val);
	size += env_key_str_len(&((*env)->next));
	return (size);
}

void	gen_env_str(t_env env, char *env_s)
{
	if (!*env)
		return ;
	ft_strcpy(env_s, (*env)->key);
	env_s = ft_strchr(env_s, '\0');
	*(env_s++) = '=';
	ft_strcpy(env_s, (*env)->val);
	gen_env_str(&((*env)->next), ft_strchr(env_s, '\0') + 1);
}

void	gen_env_str_ptrs(char **env_p, char *env_s, size_t key_total)
{
	if (!key_total)
		return ((void)(*env_p = NULL));
	*env_p = env_s;
	gen_env_str_ptrs(env_p + 1, ft_strchr(env_s, '\0') + 1, key_total - 1);
}

int		fork_exec_with_env(char *path, char **args, t_env env, int status)
{
	pid_t	pid;
	size_t	key_total;
	char	*env_p[(key_total = env_key_count(env))];
	size_t	env_str_size;
	char	env_str[(env_str_size = (env_key_str_len(env) + 1))];

	if ((pid = fork()))
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(pid, &status, 0) == -1)
			shell_pwarning("waitpid: ", "returned error status (-1)");
		signal(SIGINT, handle_sigint);
		interpret_status(status);
		return (status);
	}
	ft_bzero(env_str, env_str_size);
	gen_env_str(env, env_str);
	gen_env_str_ptrs(env_p, env_str, key_total);
	if (execve(path, args, env_p))
		shell_perror("Execve didn't override the shell's fork!");
	shell_perror("Execve failed!");
	return (-1);
}
