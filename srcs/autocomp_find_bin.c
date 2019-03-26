/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   autocomp_find_bin.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 05:09:48 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 05:11:55 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*init_find_bin_dir(char *name, char *dir_path, DIR **dir)
{
	char	*path;

	if (name[0] == '/')
		path = ft_strsub(name, 0, (size_t)(ft_strrchr(name, '/') - name));
	else
		path = ft_strdup(dir_path);
	*dir = opendir(path);
	ft_strdel(&path);
	if (!(*dir))
		return (NULL);
	if (name[0] == '/')
		return (ft_strsub(name, ft_strrchr(name, '/') - name + 1,
			ft_strlen(name) - 1 - (size_t)(ft_strrchr(name, '/') - name)));
	else
		return (ft_strdup(name));
}

char		*find_bin_dir(char *dir_path, char *name)
{
	DIR				*dir;
	struct dirent	*file;
	char			*real_name;
	int				len;

	if (!(real_name = init_find_bin_dir(name, dir_path, &dir)))
		return (NULL);
	len = ft_strlen(real_name);
	while ((file = readdir(dir)))
	{
		if (!ft_strncmp(real_name, file->d_name, len))
		{
			ft_strdel(&real_name);
			real_name = ft_strdup(file->d_name);
			closedir(dir);
			return (real_name);
		}
	}
	ft_strdel(&real_name);
	closedir(dir);
	return (NULL);
}
