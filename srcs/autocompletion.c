/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocompletion.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 17:30:27 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 05:31:15 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_path(int *curs, char cmd[], int *nb_path)
{
	char	*path;
	int		len;

	while (*curs && cmd[*curs] != ' ')
		(*curs)--;
	*curs = *curs == 0 ? 0 : *curs + 1;
	len = ft_strichr(&cmd[*curs], ' ');
	if (len == -1)
		len = ft_strlen(&cmd[*curs]);
	path = ft_strsub(&cmd[*curs], 0, len);
	if (path[0] != '/' && path[0] != '~'
		&& (*curs != 0 || is_relative_path(path)))
	{
		(*nb_path)++;
		path = ft_strfjoin(ft_strdup("./"), path);
	}
	return (path);
}

static void	insert_to_cmd(char *new_cmd, char cmd[], int *curs)
{
	int		len;
	char	*next;
	int		i;

	i = 0;
	len = ft_strichr(&cmd[*curs], ' ');
	if (len == -1)
		next = ft_strdup("\0");
	else
		next = ft_strsub(&cmd[*curs], len, ft_strlen(&cmd[*curs]) - len);
	while (new_cmd[i])
		cmd[(*curs)++] = new_cmd[i++];
	i = 0;
	while (next[i])
		cmd[(*curs)++] = next[i++];
	ft_strdel(&next);
}

static char	*get_new_command(char **path, char **env,
				char **dir_stack, int curs)
{
	int		start;
	char	*comp;
	char	*new_cmd;

	new_cmd = NULL;
	if (curs == 0 && !is_relative_path(*path))
		return (find_bin_command(path, env));
	start = ft_strrchr(*path, '/') - *path;
	comp = ft_strsub(*path, start + 1, ft_strlen(*path) - start - 1);
	if (start + 1 > 0)
		ft_strfsub(path, 0, start + 1);
	new_cmd = find_file(*path, comp, env, dir_stack);
	ft_strdel(&comp);
	return (new_cmd);
}

void		autocomplete(char cmd[], int *curs, char **env, char **dir_stack)
{
	char	*path;
	char	*new_cmd;
	int		i;
	int		nb_sub;

	nb_sub = 0;
	i = (*curs)++;
	path = get_path(&i, cmd, &nb_sub);
	new_cmd = get_new_command(&path, env, dir_stack, i);
	if (!new_cmd)
	{
		ft_strdel(&path);
		return ;
	}
	if (i != 0 || is_relative_path(path))
		new_cmd = ft_strfjoin(path, new_cmd);
	else
		ft_strdel(&path);
	while (!ft_strncmp(new_cmd, "./", 2) && (nb_sub--))
		ft_strfsub(&new_cmd, 2, ft_strlen(new_cmd) - 2);
	insert_to_cmd(new_cmd, cmd, &i);
	ft_strdel(&new_cmd);
}
