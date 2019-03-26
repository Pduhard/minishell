/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 18:07:32 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 02:18:08 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_builtin(char *name)
{
	if (!ft_strcmp(name, "cd"))
		return (BI_CD);
	else if (!ft_strcmp(name, "echo"))
		return (BI_ECHO);
	else if (!ft_strcmp(name, "setenv"))
		return (BI_SETENV);
	else if (!ft_strcmp(name, "unsetenv"))
		return (BI_UNSETENV);
	else if (!ft_strcmp(name, "env"))
		return (BI_ENV);
	else if (!ft_strcmp(name, "exit"))
		return (BI_EXIT);
	else if (!ft_strcmp(name, "dirs"))
		return (BI_DIRS);
	return (0);
}

int			is_valid_builtin(t_cmd *cmd, char ***env, t_shell *shell)
{
	int		built_in;

	if (!(built_in = check_builtin(cmd->name)))
		return (0);
	if (built_in == BI_ECHO)
		ft_echo(cmd);
	else if (built_in == BI_CD)
		return (ft_cd(cmd, *env, shell));
	else if (built_in == BI_SETENV)
		return (ft_setenv(cmd, env));
	else if (built_in == BI_UNSETENV)
		return (ft_unsetenv(cmd, *env));
	else if (built_in == BI_ENV)
		return (ft_env(cmd, *env));
	else if (built_in == BI_DIRS)
		ft_dirs(*env, shell->dir_stack);
	else if (built_in == BI_EXIT)
		ft_exit(cmd, *env, shell);
	return (1);
}
