/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_manager.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 08:39:26 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 07:01:00 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	manage_escape_seq(t_cmd_hdlr *data, char cmd[],
			char init_cmd[], t_shell *shell)
{
	if ((data->in_hist = read_escape_seq(data, cmd,
		&shell->history, shell)) == 1)
		replace_cmd(cmd, &data->index, &data->len);
	else if (data->in_hist == -1)
	{
		ft_strcat(cmd, init_cmd);
		replace_cmd(cmd, &data->index, &data->len);
	}
}

int		update_curr_cmd(char cmd[], t_cmd_hdlr *data)
{
	if (ft_strlen(cmd) == CMD_BUFF_SIZE)
		return (0);
	add_char(cmd, data->index, data->buff);
	write_cmd(cmd, data->index++, &data->len);
	return (1);
}

void	delete_chr(char cmd[], t_cmd_hdlr *data)
{
	remove_char(cmd, --data->index);
	if (data->index)
		ft_putstr("\x1b[2D");
	else
		ft_putstr("\x1b[1D");
	write_cmd(cmd, data->index - 1, &data->len);
}

void	manage_autocomp(char cmd[], t_cmd_hdlr *data,
		char **env, char **dir_stack)
{
	if (data->buff == '\t')
	{
		autocomplete(cmd, &data->index, env, dir_stack);
		replace_cmd(cmd, &data->index, &data->len);
	}
	else
		delete_chr(cmd, data);
}

void	manage_init_cmd(t_cmd_hdlr *data, char cmd[], char init_cmd[])
{
	if (!data->in_hist)
	{
		ft_bzero(init_cmd, ft_strlen(init_cmd));
		ft_strcat(init_cmd, cmd);
	}
	if (data->in_hist == -1)
		data->in_hist = 0;
}
