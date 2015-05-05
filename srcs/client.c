/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:13:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/06 00:55:05 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
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
*/

int		create_client(int port, char *addr)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		shell_perror("getprotobyname(\"tcp\") returned 0");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)))
		shell_perror("can't assign requested address");
	return (sock);
}

void	client_do(int sock, char *buf)
{
	int		ret;

	if (ft_strequ(buf, "help"))
		ft_putstr(HELP);
	else if (ft_strncmp(buf, "get ", 4) == 0)
		client_get(sock, buf);
	else if (ft_strncmp(buf, "put ", 4) == 0)
		client_put(sock, buf);
	else
	{
		server_sendstr(sock, buf);
		ret = recv(sock, buf, BUF_SIZE, 0);
		buf[ret] = '\0';
		ft_putendl(buf);
	}
}

void	handle_sigpipe(int signum)
{
	(void)signum;
	shell_perror("Server connection lost!");
}

void	client(int sock, char *path)
{
	char	buf[BUF_SIZE + 1];
	int		ret;

	signal(SIGTSTP, exit);
	signal(SIGPIPE, handle_sigpipe);
	ft_putstr(WELCOME);
	while (ft_putfourstr(path, " ", PROMPT, NULL), 1)
	{
		if (ret = read(0, buf, BUF_SIZE), ret > 0)
		{
			buf[ret] = '\0';
			if (ft_strequ(buf, "quit"))
			{
				server_sendstr(sock, buf);
				ft_putstr(GOODBYE);
				exit(0);
			}
			client_do(sock, buf);
		}
		else
		{
			ft_putstr(GOODBYE);
			exit(0);
		}
	}
}

int		main(int argc, char **argv)
{
	int		port;
	int		sock;
	int		ret;
	char	buf[BUF_SIZE + 1];
	char	*path;

	if (argc != 3)
		shell_perror("USAGE: ./client [machine] [port]");
	port = ft_atoi(argv[2]);
	sock = create_client(port, argv[1]);
	ret = recv(sock, buf, BUF_SIZE, 0);
	buf[ret] = '\0';
	ft_putendl(buf);
	path = ft_strjoin(argv[1], ":");
	ft_strjoinfree(&path, argv[2]);
	client(sock, path);
	close(sock);
	return (0);
}
