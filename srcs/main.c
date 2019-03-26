/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 07:06:48 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 07:02:22 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_input(char **env, t_shell *shell, char **line)
{
	char	*tmp;

	shell->prompt_len = print_prompt(env, shell->cmd_ret);
	if (!get_command(line, shell, env))
	{
		free(shell);
		signal(2, SIG_DFL);
		exit(EXIT_SUCCESS);
	}
	tmp = ft_strtrim(*line);
	ft_strdel(line);
	*line = tmp;
}

static void	command_loop(t_cmd **cmd, t_shell *shell, char ***env)
{
	while (*cmd)
	{
		if ((shell->cmd_ret = is_valid_builtin(*cmd, env, shell)))
			shell->cmd_ret = shell->cmd_ret == 1 ? 0 : 1;
		else if (is_valid_bin(*cmd, *env))
		{
			if (access((*cmd)->bin_path, X_OK) == -1)
				shell->cmd_ret = ft_printf("%s%s\n",
					"minishell: permission denied: ", (*cmd)->name);
			else if (!is_empty((*cmd)->name))
				shell->cmd_ret = launch_exec((*cmd)->name,
					(*cmd)->argv, *env, (*cmd)->bin_path);
		}
		else
		{
			ft_printf("minishell: command not found: %s\n",
				(*cmd)->name, (*cmd)->bin_path);
			shell->cmd_ret = 1;
		}
		*cmd = free_and_next_cmd(cmd);
	}
}

static void	shell_loop(char **env, t_shell *shell)
{
	char	*line;
	t_cmd	*cmd;

	line = NULL;
	shell->cmd_ret = 0;
	signal(2, SIG_IGN);
	while (1)
	{
		get_input(env, shell, &line);
		if (shell->interupt == 0 && line[0]
			&& (cmd = parse_command(&line, env, shell->dir_stack)))
		{
			if (!is_empty(line))
				add_history_command(&shell->history, line);
			ft_strdel(&line);
			command_loop(&cmd, shell, &env);
		}
		else
			ft_strdel(&line);
		if (shell->interupt)
			shell->cmd_ret = 1;
		shell->interupt = 0;
	}
}

int			main(void)
{
	char	**env;
	t_shell	*shell;

	env = NULL;
	shell = NULL;
	if (!(env = get_environ())
		|| !(shell = init_shell(env)))
		return (-1);
	shell_loop(env, shell);
	return (0);
}
