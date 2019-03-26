/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 16:07:17 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 04:02:29 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*ret_and_free(char **dirs, char *bin_path)
{
	int		i;

	i = 0;
	while (dirs && dirs[i])
		ft_strdel(&dirs[i++]);
	if (dirs)
		free(dirs);
	return (bin_path);
}

char			*get_bin_path(char **param, t_env *data)
{
	char		**dirs;
	int			i;
	char		*bin_path;
	struct stat	info;

	i = -1;
	if (param && is_relative_path(param[0]))
		return (ft_strdup(param[0]));
	dirs = NULL;
	if (data->alpath)
		dirs = ft_strsplit(data->alpath, ':');
	while (dirs && param && dirs[++i])
	{
		bin_path = ft_strjoin(dirs[i], "/");
		bin_path = ft_strfjoin(bin_path, ft_strdup(param[0]));
		if (lstat(bin_path, &info) != -1)
			return (ret_and_free(dirs, bin_path));
		ft_strdel(&bin_path);
	}
	i = 0;
	while (dirs && dirs[i])
		ft_strdel(&dirs[i++]);
	if (dirs)
		free(dirs);
	return (NULL);
}

static t_env	*init_env(char **arg, int *i, char **env_vars)
{
	t_env	*data;

	*i = 1;
	if (!(data = (t_env *)malloc(sizeof(t_env))) && env_vars)
		return (NULL);
	ft_bzero(data, sizeof(t_env));
	while (!data->maj_s && arg[*i] && arg[*i][0] == '-')
	{
		if (!update_option(&arg[*i][1], data, arg, i))
		{
			free(data);
			return (NULL);
		}
		if (arg[*i])
			*i += 1;
	}
	if (!data->alpath)
		data->alpath = find_env_val(env_vars, "PATH=");
	data->env = build_new_env(env_vars, data, arg, i);
	data->param = build_param(data, arg, i);
	*i = 0;
	return (data);
}

static int		env_launch_exec(t_env *data)
{
	launch_exec(data->param[0], data->param, data->env, data->bin_path);
	free_env_struct(data);
	return (1);
}

int				ft_env(t_cmd *cmd, char **env)
{
	int		i;
	t_env	*data;

	if (!(data = init_env(cmd->argv, &i, env)))
		return (-1);
	if (!data->param || !data->param[0])
	{
		while (data->env && data->env[i])
			ft_putendl(data->env[i++]);
		free_env_struct(data);
		return (1);
	}
	else
	{
		if (!data->bin_path)
			ft_printf("env: %s: No such file or directory.\n", data->param[0]);
		else if (access(data->bin_path, X_OK) == -1
			|| !check_is_file(data->bin_path))
			ft_printf("env: %s: Permission denied.\n", data->param[0]);
		else
			return (env_launch_exec(data));
	}
	free_env_struct(data);
	return (-1);
}
