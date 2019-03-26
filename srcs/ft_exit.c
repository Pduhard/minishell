/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_exit.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 19:07:08 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 04:08:57 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_shell(t_shell *shell)
{
	int		i;
	t_hist	*next;

	i = 0;
	while (shell->dir_stack && shell->dir_stack[i])
		ft_strdel(&shell->dir_stack[i++]);
	free(shell->dir_stack);
	while (shell->history->prev)
		shell->history = shell->history->prev;
	while (shell->history)
	{
		ft_strdel(&shell->history->command);
		next = shell->history->next;
		free(shell->history);
		shell->history = next;
	}
	free(shell);
}

static void	free_stuff(t_cmd *cmd, char **env, t_shell *shell)
{
	t_cmd	*next;
	int		i;

	while (cmd)
	{
		next = cmd->next;
		free_command(cmd);
		cmd = next;
	}
	i = 0;
	free_shell(shell);
	while (env[i])
		ft_strdel(&env[i++]);
	if (env)
		free(env);
}

void		ft_exit(t_cmd *cmd, char **env, t_shell *shell)
{
	int		i;
	int		status;

	i = 0;
	status = shell->cmd_ret;
	if (cmd->argv[1])
		status = ft_atoi(cmd->argv[1]);
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_printf("exit: too many arguments\n");
		return ;
	}
	add_history_command(&shell->history, "exit");
	save_history(shell->history, find_env_val(env, "HOME="));
	free_stuff(cmd, env, shell);
	ft_putstr("exit\n");
	exit(status);
}
