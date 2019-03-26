/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 16:50:50 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/17 13:25:32 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;
	char	*pwd;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	ft_bzero((void *)shell, sizeof(t_shell));
	shell->history = get_history(find_env_val(env, "HOME="));
	if ((pwd = find_env_val(env, "PWD=")))
	{
		add_dir_to_stack(&shell->dir_stack, pwd);
		ft_strdel(&pwd);
	}
	return (shell);
}
