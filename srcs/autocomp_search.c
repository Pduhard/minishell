/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp_search.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 04:30:31 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 04:44:40 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	match_file(struct dirent *file, char *comp, char **save, int len)
{
	if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, "..")
			&& !ft_strncmp(comp, file->d_name, len))
	{
		ft_strdel(save);
		*save = ft_strdup(file->d_name);
		return (1);
	}
	return (0);
}

char		*find_file(char *path, char *comp, char **env, char **dir_stack)
{
	DIR				*rep;
	struct dirent	*file;
	char			*save;
	int				count;
	char			*real_path;

	real_path = ft_strdup(path);
	replace_tilde_exp(&real_path, env, dir_stack);
	count = 0;
	save = NULL;
	if (!(rep = opendir(real_path)))
	{
		ft_strdel(&real_path);
		return (NULL);
	}
	while ((file = readdir(rep)))
		if (match_file(file, comp, &save, ft_strlen(comp)))
			count++;
	if (count > 1)
		ft_strdel(&save);
	else if (!count)
		write(1, "\a", 1);
	closedir(rep);
	ft_strdel(&real_path);
	return (save);
}

static char	*free_and_ret(char **dirs_path, char **comp, char *new_cmd)
{
	int		i;

	i = 0;
	while (dirs_path[i])
		ft_strdel(&dirs_path[i++]);
	free(dirs_path);
	ft_strdel(comp);
	return (new_cmd);
}

static char	**init_find_param(char **env, char **comp, char *path)
{
	int		len;
	char	*env_path;
	char	**dirs_path;

	len = ft_strichr(path, ' ');
	if (len == -1)
		len = ft_strlen(path);
	*comp = ft_strsub(path, 0, len);
	env_path = NULL;
	if ((!(env_path = find_env_val(env, "PATH=")) && (*comp)[0] != '/')
		|| !(dirs_path = ft_strsplit(env_path, ':')))
	{
		ft_strdel(comp);
		ft_strdel(&env_path);
		return (NULL);
	}
	ft_strdel(&env_path);
	return (dirs_path);
}

char		*find_bin_command(char **path, char **env)
{
	char	**dirs_path;
	int		i;
	char	*tmp;
	char	*new_cmd;
	char	*comp;

	i = 0;
	if (!(dirs_path = init_find_param(env, &comp, *path)))
		return (NULL);
	new_cmd = NULL;
	while (dirs_path[i])
	{
		if ((tmp = find_bin_dir(dirs_path[i], comp)))
		{
			ft_strdel(&new_cmd);
			new_cmd = tmp;
			return (free_and_ret(dirs_path, &comp, new_cmd));
		}
		i++;
	}
	return (free_and_ret(dirs_path, &comp, NULL));
}
