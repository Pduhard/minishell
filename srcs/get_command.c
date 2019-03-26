/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_command.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 03:35:06 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 07:01:50 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	enable_raw_mode(struct termios *raw)
{
	struct termios	orig;

	tcgetattr(STDIN_FILENO, raw);
	tcgetattr(STDIN_FILENO, &orig);
	orig.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}

static void	init_get_command(char cmd[], char init_cmd[], t_cmd_hdlr *data)
{
	ft_bzero(data, sizeof(t_cmd_hdlr));
	ft_bzero(cmd, CMD_BUFF_SIZE);
	ft_bzero(init_cmd, CMD_BUFF_SIZE);
	enable_raw_mode(&data->raw);
}

static int	clean_exit(char **line, t_shell *shell,
				char **env, t_cmd_hdlr *data)
{
	t_hist	*next;
	int		i;

	ft_strdel(line);
	while (shell && shell->history && shell->history->prev)
		shell->history = shell->history->prev;
	while (shell && shell->history)
	{
		next = shell->history->next;
		ft_strdel(&shell->history->command);
		free(shell->history);
		shell->history = next;
	}
	i = 0;
	while (env && env[i])
		ft_strdel(&env[i++]);
	if (!(i = 0) && env)
		free(env);
	while (shell && shell->dir_stack && shell->dir_stack[i])
		ft_strdel(&shell->dir_stack[i++]);
	if (shell && shell->dir_stack)
		free(shell->dir_stack);
	go_to_end(NULL, data, shell);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->raw);
	return (0);
}

static int	return_command(t_cmd_hdlr *data, char **line,
				char cmd[], char init_cmd[])
{
	write(0, "\n", 1);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->raw);
	*line = !data->interupt ? ft_strdup(cmd) : NULL;
	ft_bzero(cmd, ft_strlen(cmd));
	ft_bzero(init_cmd, ft_strlen(init_cmd));
	return (1);
}

int			get_command(char **line, t_shell *shell, char **env)
{
	char		cmd[CMD_BUFF_SIZE];
	char		init_cmd[CMD_BUFF_SIZE];
	t_cmd_hdlr	data;

	init_get_command(cmd, init_cmd, &data);
	while (read(0, &data.buff, 1) && data.buff != '\n')
	{
		if (data.buff == 3)
		{
			go_to_end(cmd, &data, shell);
			break ;
		}
		if (data.buff == '\x1b')
			manage_escape_seq(&data, cmd, init_cmd, shell);
		else if (ft_isprint(data.buff) && !update_curr_cmd(cmd, &data))
			break ;
		else if (data.buff == 4 || data.buff == 28)
			return (clean_exit(line, shell, env, &data));
		else if (data.buff == '\t' || (data.buff == 127 && data.index > 0))
			manage_autocomp(cmd, &data, env, shell->dir_stack);
		manage_init_cmd(&data, cmd, init_cmd);
	}
	while (shell->history && shell->history->prev)
		shell->history = shell->history->prev;
	return (return_command(&data, line, cmd, init_cmd));
}
