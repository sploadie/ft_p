/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/24 12:00:25 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void	handle_input(char *str, t_env env)
{
	t_args		*args;
	t_spl_func	*spl_function;
	int			status;

	status = 0;
	args = parse_input_args(env, str, 1);
	if ((spl_function = get_spl_function(args->args[0])))
		(*spl_function)(args, env);
	else if ((str = get_exec_path(env, args->args[0])))
		fork_exec_with_env(str, args->args, env, status);
	del_input_args(&args);
}

int			main(int argc, char **argv, char **environ)
{
	t_env		env;
	char		*str;

	(void)argc;
	(void)argv;
	env = init_shell_env(environ);
	signal(SIGINT, handle_sigint);
	signal(SIGCONT, handle_sigint);
	ft_putstr(str = WELCOME);
	while (1)
	{
		ft_putstr(PROMPT);
		if (read_stdin(env, &str), !*str)
		{
			free(str);
			continue ;
		}
		handle_input(str, env);
	}
	shell_perror("END OF MAIN REACHED");
	return (0);
}
