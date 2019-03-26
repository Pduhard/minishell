/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_exec.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 08:44:57 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 11:35:36 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		move_left(t_cmd_hdlr *data)
{
	if (data->index != 0)
	{
		data->index--;
		ft_putstr("\x1b[1D");
	}
	return (data->in_hist ? 2 : 0);
}

int		move_right(t_cmd_hdlr *data, char cmd[], int prompt_len)
{
	struct winsize	win;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win) == -1)
		return (data->in_hist ? 2 : 0);
	if (data->index != (int)ft_strlen(cmd))
	{
		data->index++;
		if ((data->index + prompt_len) % (win.ws_col) == 0)
		{
			write(1, &cmd[data->index - 1], 2);
			ft_putstr("\x1b[1D");
		}
		else
			ft_putstr("\x1b[1C");
	}
	return (data->in_hist ? 2 : 0);
}

int		history_up(t_cmd_hdlr *data, t_hist **history, char cmd[])
{
	if (*history && (!(*history)->prev || ((*history)->next)))
	{
		ft_bzero(cmd, ft_strlen(cmd));
		if (data->in_hist && (*history)->next)
			*history = (*history)->next;
		ft_strcat(cmd, (*history)->command);
		if (data->index)
			ft_putstr("\x1b[1D");
		return (1);
	}
	if (*history && (*history)->next)
		return (1);
	else
		return (2);
}

int		history_down(t_cmd_hdlr *data, t_hist **history, char cmd[])
{
	if (*history)
	{
		if (data->in_hist && (*history)->prev)
		{
			*history = (*history)->prev;
			ft_bzero(cmd, ft_strlen(cmd));
			ft_strcat(cmd, (*history)->command);
			if (data->index)
				write(1, "\x1b[1D", ft_strlen("\x1b[1D"));
			return (1);
		}
		else if (data->in_hist)
		{
			if (data->index)
				write(1, "\x1b[1D", ft_strlen("\x1b[1D"));
			ft_bzero(cmd, ft_strlen(cmd));
			return (-1);
		}
	}
	return (0);
}

char	*create_escape_seq(int i, char *code)
{
	char	*seq;
	char	*tmp;

	seq = ft_strdup("\x1b[");
	seq = ft_strfjoin(seq, ft_itoa(i));
	tmp = ft_strjoin(seq, code);
	ft_strdel(&seq);
	return (tmp);
}
