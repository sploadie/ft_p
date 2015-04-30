/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 17:30:44 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/23 12:09:53 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void	exit_status(int ret)
{
	char	str[2];

	if (!ret)
		return ;
	str[0] = '0' + ret;
	str[1] = '\0';
	shell_pwarning("process exited normally with status ", str);
}

static char	*sig_name(int sig)
{
	char	*name;

	name = NULL;
	name = (sig == 1 ? " (SIGHUP: terminal line hangup)" : name);
	name = (sig == 2 ? " (SIGINT: interrupt program)" : name);
	name = (sig == 3 ? " (SIGQUIT: quit program)" : name);
	name = (sig == 4 ? " (SIGILL: illegal instruction)" : name);
	name = (sig == 5 ? " (SIGTRAP: trace trap)" : name);
	name = (sig == 6 ? " (SIGABRT: abort program)" : name);
	name = (sig == 7 ? " (SIGEMT: emulate instruction executed)" : name);
	name = (sig == 8 ? " (SIGFPE: floating-point exception)" : name);
	name = (sig == 9 ? " (SIGKILL: kill program)" : name);
	name = (sig == 10 ? " (SIGBUS: bus error)" : name);
	name = (sig == 11 ? " (SIGSEGV: segmentation violation)" : name);
	name = (sig == 12 ? " (SIGSYS: non-existent system call invoked)" : name);
	name = (sig == 14 ? " (SIGALRM: real-time timer expired)" : name);
	name = (sig == 15 ? " (SIGTERM: software termination signal)" : name);
	name = (sig == 16 ? " (SIGURG: urgent condition present on socket)" : name);
	name = (sig == 17 ? " (SIGSTOP: stop (can't be caught or ignored))" : name);
	name = (sig == 18 ? " (SIGTSTP: stop signal from keyboard)" : name);
	name = (sig == 19 ? " (SIGCONT: continue after stop)" : name);
	name = (sig == 20 ? " (SIGCHLD: child status has changed)" : name);
	return (name);
}

static void	stop_status(int signum)
{
	shell_psignal(NULL, signum, " paused your process", sig_name(signum));
}

static void	signal_status(int signum)
{
	shell_psignal(NULL, signum, " terminated your process", sig_name(signum));
}

void		interpret_status(int status)
{
	if (WIFEXITED(status))
		exit_status(WEXITSTATUS(status));
	if (WIFSTOPPED(status))
		stop_status(WSTOPSIG(status));
	if (WIFSIGNALED(status))
		signal_status(WTERMSIG(status));
}
