/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 04:01:48 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 04:03:11 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_command(t_cmd *cmd)
{
	int		i;

	i = 0;
	ft_strdel(&cmd->name);
	ft_strdel(&cmd->bin_path);
	while (cmd->argv && cmd->argv[i])
		ft_strdel(&cmd->argv[i++]);
	if (cmd->argv)
		free(cmd->argv);
	free(cmd);
}

void	free_env_struct(t_env *data)
{
	int		i;

	i = 0;
	ft_strdel(&data->alpath);
	ft_strdel(&data->string);
	while (data->names && data->names[i])
		ft_strdel(&data->names[i++]);
	if (data->names)
		free(data->names);
	ft_strdel(&data->bin_path);
	i = 0;
	while (data->param && data->param[i])
		ft_strdel(&data->param[i++]);
	if (data->param)
		free(data->param);
	i = 0;
	while (data->env && data->env[i])
		ft_strdel(&data->env[i++]);
	if (data->env)
		free(data->env);
	free(data);
}
