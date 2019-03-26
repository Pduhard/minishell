/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 01:50:44 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 06:04:19 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_pid;
int		g_status;

void	handle_signal(int sig)
{
	if (sig)
		;
	g_pid = wait(&g_status);
}

void	print_sig_error(int sig, pid_t pid, char *name)
{
	if (sig == SIGFPE)
		ft_printf("[1]\t%d floating point exception  %s\n", pid, name);
	if (sig == SIGSEGV)
		ft_printf("[1]\t%d segmentation fault  %s\n", pid, name);
	if (sig == SIGILL)
		ft_printf("[1]\t%d illegal hardware instruction  %s\n", pid, name);
	if (sig == SIGBUS)
		ft_printf("[1]\t%d bus error  %s\n", pid, name);
	if (sig == SIGTRAP)
		ft_printf("[1]\t%d trace trap  %s\n", pid, name);
	if (sig == SIGEMT)
		ft_printf("[1]\t%d EMT instruction  %s\n", pid, name);
	if (sig == SIGSYS)
		ft_printf("[1]\t%d invalid system call  %s\n", pid, name);
}

int		launch_exec(char *name, char **argv, char **env, char *bin_path)
{
	pid_t	child;
	int		ret;

	signal(SIGCHLD, &handle_signal);
	child = fork();
	ret = -1;
	if (!child)
	{
		signal(2, SIG_DFL);
		execve(bin_path, argv, env);
	}
	else
	{
		g_pid = wait(&g_status);
		ret = WEXITSTATUS(g_status);
		if (WIFEXITED(g_status))
			return (ret);
		else if (WIFSIGNALED(g_status))
			print_sig_error(WTERMSIG(g_status), child, name);
		return (-1);
	}
	return (ret);
}
