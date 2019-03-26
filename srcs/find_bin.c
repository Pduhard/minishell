/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_bin.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 15:47:32 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 05:28:43 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**parse_path(char **env)
{
	char	**path_dirs;
	int		i;
	char	*path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	if (!(path = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5)))
		return (NULL);
	path_dirs = ft_strsplit(path, ':');
	ft_strdel(&path);
	return (path_dirs);
}

int			is_relative_path(char *path)
{
	if (!path)
		return (0);
	if (path[0] == '/')
		return (1);
	if (path[0] == '.' && path[1] == '/')
		return (1);
	if (path[0] == '.' && path[1] == '.' && path[2] == '/')
		return (1);
	return (0);
}

static int	is_valid_bin_path(t_cmd *cmd)
{
	struct stat		info;

	if (is_relative_path(cmd->name))
	{
		if (lstat(cmd->name, &info) != -1)
		{
			if ((info.st_mode & S_IFMT) == S_IFREG)
			{
				cmd->bin_path = ft_strdup(cmd->name);
				return (1);
			}
		}
		return (-1);
	}
	return (0);
}

static int	free_and_ret(char **path_dirs, t_cmd *cmd, int ret)
{
	int		i;

	i = 0;
	while (path_dirs[i])
		ft_strdel(&path_dirs[i++]);
	if (ret == 1)
	{
		ft_strdel(&cmd->argv[0]);
		cmd->argv[0] = ft_strdup(cmd->bin_path);
	}
	free(path_dirs);
	return (ret);
}

int			is_valid_bin(t_cmd *cmd, char **env)
{
	char		**path_dirs;
	int			i;
	int			ret;
	struct stat info;

	i = 0;
	if ((ret = is_valid_bin_path(cmd)))
		return (ret == -1 ? 0 : 1);
	if (!ft_strcmp(cmd->name, ".")
		|| !ft_strcmp(cmd->name, "..")
			|| !(path_dirs = parse_path(env)))
		return (0);
	while (path_dirs[i])
	{
		cmd->bin_path = ft_strjoin(path_dirs[i], "/");
		cmd->bin_path = ft_strfjoin(cmd->bin_path, ft_strdup(cmd->name));
		if (lstat(cmd->bin_path, &info) != -1)
			return (free_and_ret(path_dirs, cmd, 1));
		ft_strdel(&cmd->bin_path);
		i++;
	}
	return (free_and_ret(path_dirs, cmd, 0));
}
