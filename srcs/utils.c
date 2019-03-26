/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 09:55:03 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 06:55:57 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*free_and_next_cmd(t_cmd **cmd)
{
	int		i;
	t_cmd	*next;

	i = 0;
	if ((*cmd)->argv)
	{
		while ((*cmd)->argv[i])
			ft_strdel(&(*cmd)->argv[i++]);
		free((*cmd)->argv);
	}
	ft_strdel(&(*cmd)->name);
	ft_strdel(&(*cmd)->bin_path);
	next = (*cmd)->next;
	free(*cmd);
	return (next);
}

int		check_empty(int fd, char *str)
{
	char	*line;
	int		i;
	int		check;

	line = NULL;
	check = 0;
	while (*str && !ft_isspace(*str) && (check = 1))
		str++;
	while (ft_isspace(*str))
		str++;
	if (!check || *str)
		return (0);
	check = 1;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (line[i])
			if (!ft_isspace(line[i++]))
				check = 0;
		ft_strdel(&line);
	}
	return (check);
}

int		is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

void	go_to_end(char cmd[], t_cmd_hdlr *data, t_shell *shell)
{
	while (cmd && cmd[data->index])
		write(1, &cmd[data->index++], 1);
	if (!cmd)
		write(1, "\n", 1);
	shell->interupt = 1;
	data->interupt = 1;
}
