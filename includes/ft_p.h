/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:12:51 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/05/07 15:49:11 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# include <stdio.h>

# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "libft.h"
# include "filedir.h"
# include "get_next_line.h"

/*
** malloc
** free
** read
** write
** exit				(3)
** open				(2)
** close			(2)
** printf			(3)
** signal			(3)
** opendir			(3)
** readdir			(3)
** closedir			(3)
** fstat			(2)
** chdir			(2)
** mkdir			(2)
*/

/*
** socket			(2)	int socket(int domain, int type, int protocol);
** 							domain: <sys/socket.h> contains protocol families.
** 									(Use PF_INET)
** 							type:	SOCK_
** 								STREAM: provides sequenced, reliable,
** 										two-way connection based byte streams
** 								DGRAM: supports datagrams
** 										(connectionless, unreliable messages of a
** 										fixed (typically small) maximum length)
** 								RAW: provides access to internal network
** 										protocols and interfaces
** 								SEQPACKET: presently implemented only for PF_NS
** 								RDM: not yet implemented
** 							protocol: see protocols(5)
** setsockopt		(2) int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
** 							socket: socket in question
** 							level: options at the socket level: SOL_SOCKET
** 								at any other level the protocol number of the appropriate protocol controlling the option is supplied
** 								for example, to indicate that an option is to be interpreted by the TCP protocol,
** 								level should be set to the protocol number of TCP; see getprotoent(3)
** 							option_name:
** 							option_value: may be NULL
** 							option_len:
** getsockname		(2) int getsockname(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
** 							socket: socket in question
** 							address: contains address structure on return (must be allocated)
** 							address_len: contains address size on return (initially should be allocated size)
** getprotobyname	(3) struct protoent *getprotobyname(const char *name);
** 							name: name of protocol you want (use "tcp")
** 							returns protocol struct, or null if error
** gethostbyname	(3) struct hostent *gethostbyname(const char *name);
** 							getaddrinfo(3) is preferred over gethostbyname(3)
** getaddrinfo		(3) int getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
** 							hostname: valid host name OR numeric host address string (dotted decimal IPv4/IPv6 address)
** 							servname: decimal port number OR service name listed in services(5)
** 								(hostname and/or servname must be non-NULL)
** 							hints: optional pointer to a struct addrinfo, as defined by <netdb.h> (see MAN)
** 							res: on success, *res is a pointer to a linked list of one or more addrinfo structures:
** 								traverse list by following the 'ai_next' pointers until a null pointer is encountered
** 								'ai_family', 'ai_socktype', and 'ai_protocol' in each struct are suitable for a call to socket(2)
** 								for each struct in the list, the 'ai_addr' member points to a socket address struct of length 'ai_addrlen'
** bind				(2) int bind(int socket, const struct sockaddr *address, socklen_t address_len);
** 							socket: local socket
** 							address: address to be assigned to socket
** 							address_len:
** connect			(2) int connect(int socket, const struct sockaddr *address, socklen_t address_len);
** 							socket: local socket
** 							address: address of socket trying to connect to
** 							address_len: size of address?
** 							(See man for error types)
** listen			(2) int listen(int socket, int backlog);
** 							socket: socket which wants to listen
** 							backlog: max number of queuing connections (1)
** accept			(2) int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
** 							socket: socket which wants to listen
** 							address: fills in with info
** 							address_len: contains address size on return (initially should be allocated size)
** 							contains fd upon success, -1 on failure
** htons			(3) uint16_t htons(uint16_t hostshort);
** htonl			(3) uint32_t htonl(uint32_t hostlong);
** ntohs			(3) uint16_t ntohl(uint32_t netlong);
** ntohl			(3) uint32_t ntohs(uint16_t netshort);
** inet_addr		(3)
** inet_ntoa		(3)
** send				(2) ssize_t send(int socket, const void *buffer, size_t length, int flags);
** recv				(2)
** execv			(2)
** execl			(2)
** dup2				(2)
** wait4			(2)
** fork				(2)
** getcwd			(3)
** mmap				(2)
** munmap			(2)
** lseek			(2)
** unlink			(2)
*/

# define BUF_SIZE 1024
# define SERVER_DIR "./server_space"

void	handle_signals(int signum);

char	*server_root_dir(void);

void	server_sendstr(int cs, char *str, size_t length);
void	server_sendbuf(int cs, char *str);
void	server_sendint(int sock, int num);
int		server_recvstr(int sock, char *buf, size_t length);
int		server_recvbuf(int sock, char *buf);
int		server_recvint(int sock);

void	server_ls(int cs);
void	server_cd(int cs, char *path);
void	server_pwd(int cs);
void	server_get(int cs, char *cmd);
void	server_put(int cs, char *cmd);
void	server_mkdir(int cs, char *dirname);

void	client_ls(int sock);
void	client_get(int sock, char *buf);
void	client_put(int sock, char *buf);

/*
** Shell permitted functions:
** stat
** lstat
** execve
** access
** wait
** waitpid
** wait3
** kill
*/

# define INPUT_MAX_ARGS 200
# define ESCAPE_CHARS " \t"
# define WE "\x1b[32m\nWelcome to sploadieClient.\nIs it time to play?\n\x1b[0m"
# define WELCOME WE
# define HELP "\x1b[32mMaybe next time, sir.\n\x1b[0m"
# define GOODBYE "\x1b[32mUntil next time, sir.\n\x1b[0m"
# define PROMPT "\x1b[32m$pl > \x1b[0m"
# define QUOTE_PROMPT "\x1b[32m\" > \x1b[0m"
# define RET_PROMPT "\x1b[31msploadieClient: \x1b[0m"

typedef struct			s_env_key
{
	char				*key;
	char				*val;
	struct s_env_key	*next;
}						t_env_key;

typedef struct			s_args
{
	char				*str;
	char				**args;
	size_t				arg_count;
}						t_args;

/*
** After init, t_env should never be called except as '*env'.
*/

typedef t_env_key		**t_env;

typedef void			(t_spl_func)(t_args *args, t_env env);

void					shell_perror(char *s);
void					*shell_pwarning(char *s1, char *s2);
void					shell_psignal(char *s1, int signum,
										char *s2, char *signame);
void					handle_sigint(int sig);
void					handle_sigtstp(int sig);
void					interpret_status(int status);

void					read_stdin(t_env env, char **line);
void					ft_sort_string_array(char **string_array, int size);
void					ft_strjoinfree(char **line, char *add);
void					ft_putfourstr(char *s1, char *s2, char *s3, char *s4);

t_spl_func				*get_spl_function(char *str);
void					sploadie_cd(t_args *args, t_env env);
void					sploadie_setenv(t_args *args, t_env env);
void					sploadie_unsetenv(t_args *args, t_env env);
void					sploadie_env(t_args *args, t_env env);

int						isdir(char *path);

t_env					init_shell_env(char **environ);
char					*key_key_str(char *env_str);
char					*key_val_str(char *env_str);

t_env_key				*gen_env_key(char *key, char *val, t_env_key *next);
void					add_env_key(t_env env, char *neokey, char *neoval);
int						del_env_key(t_env env, char *del_key);

t_env_key				*fetch_env_key(t_env env, char *key_str);
char					*fetch_key_val(t_env env, char *key_str);
void					print_env(t_env env);
size_t					env_key_count(t_env env);

t_args					*parse_input_args(t_env env, char *input, int isalloc);
void					del_input_args(t_args **args);

char					*get_exec_path(t_env env, char *cmd);
int						fork_exec_with_env(char *path, char **args,
											t_env env, int status);

char					*append_quote(t_env env, char *str);

#endif
