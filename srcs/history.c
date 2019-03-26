/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 08:34:16 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 11:54:51 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_hist	*new_hist(char *cmd)
{
	t_hist	*hist;

	if (!(hist = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	hist->command = ft_strdup(cmd);
	hist->prev = NULL;
	hist->next = NULL;
	return (hist);
}

void	add_history_command(t_hist **history, char *cmd)
{
	t_hist	*hist;

	if (!(hist = new_hist(cmd)))
		return ;
	if (*history)
	{
		(*history)->prev = hist;
		hist->next = *history;
	}
	*history = hist;
}

void	save_history(t_hist *history, char *home)
{
	int		fd;
	char	*path;

	path = ft_strfjoin(home, ft_strdup("/.minishell_history"));
	if ((fd = open(path, O_TRUNC | O_WRONLY | O_CREAT)) > 0)
	{
		while (history->next)
			history = history->next;
		while (history)
		{
			write(fd, history->command, ft_strlen(history->command));
			write(fd, "\n", 1);
			history = history->prev;
		}
	}
	ft_strdel(&path);
}

t_hist	*get_history(char *home)
{
	char	*path;
	t_hist	*hist;
	char	*line;
	int		fd;

	if (!home)
		return (NULL);
	path = ft_strfjoin(home, ft_strdup("/.minishell_history"));
	hist = NULL;
	if ((fd = open(path, O_RDONLY)) > 0)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			add_history_command(&hist, line);
			ft_strdel(&line);
		}
	}
	ft_strdel(&path);
	return (hist);
}
