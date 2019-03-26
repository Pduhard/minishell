/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsetenv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 01:16:15 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 04:07:31 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_unsetenv(t_cmd *cmd, char **env)
{
	int		i;

	i = 1;
	if (!cmd->argv[i])
	{
		ft_printf("unsetenv: Too few arguments.\n");
		return (-1);
	}
	remove_env_var(cmd->argv, env, 1);
	return (1);
}
