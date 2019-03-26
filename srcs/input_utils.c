/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 08:42:59 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 05:22:01 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		read_escape_seq(t_cmd_hdlr *data, char cmd[],
			t_hist **history, t_shell *shell)
{
	read(0, &data->buff, 1);
	read(0, &data->buff, 1);
	if (data->buff == 68 && history)
		return (move_left(data));
	if (data->buff == 65)
		return (history_up(data, history, cmd));
	if (data->buff == 67)
		return (move_right(data, cmd, shell->prompt_len));
	if (data->buff == 66)
		return (history_down(data, history, cmd));
	return (0);
}

void	add_char(char cmd[], int i, char c)
{
	char	tmp;

	if (!cmd[i])
		cmd[i] = c;
	else
	{
		while (c)
		{
			tmp = cmd[i];
			cmd[i++] = c;
			c = tmp;
		}
	}
}

void	remove_char(char cmd[], int i)
{
	if (i >= 0)
		cmd[i] = '\0';
	while (cmd[i + 1])
	{
		cmd[i] = cmd[i + 1];
		cmd[++i] = '\0';
	}
}

void	replace_cmd(char cmd[], int *i, int *len)
{
	char	*back;
	char	*blank;

	back = create_escape_seq((*i) - 1, "D");
	blank = ft_strfillnew(' ', *len);
	if (*i - 1 > 0)
		ft_putstr(back);
	ft_strdel(&back);
	back = create_escape_seq(*len, "D");
	ft_putstr(blank);
	if (*len > 0)
		ft_putstr(back);
	ft_putstr(cmd);
	*len = ft_strlen(cmd);
	*i = *len;
	ft_strdel(&back);
	ft_strdel(&blank);
}

void	write_cmd(char cmd[], int i, int *len)
{
	char	*back;
	char	*front;
	char	*blank;

	back = create_escape_seq(i, "D");
	blank = ft_strfillnew(' ', *len);
	if (i > 0)
		ft_putstr(back);
	ft_strdel(&back);
	back = create_escape_seq(*len, "D");
	ft_putstr(blank);
	if (*len > 0)
		ft_putstr(back);
	ft_putstr(cmd);
	*len = ft_strlen(cmd);
	front = create_escape_seq(*len - i - 1, "D");
	if (*len - i - 1 > 0)
		ft_putstr(front);
	ft_strdel(&back);
	ft_strdel(&front);
	ft_strdel(&blank);
}
