/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_utils.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 03:28:53 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 03:39:29 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	unset_new_env(t_env *data, char **env)
{
	int		i;

	remove_env_var(data->names, env, 0);
	i = 0;
	while (data->v && data->names && data->names[i])
	{
		data->names[i][ft_strlen(data->names[i]) - 1] = '\0';
		ft_printf("#env unset:\t%s\n", data->names[i++]);
	}
}

static char	**init_new_env(t_env *data, char **env_vars)
{
	int		i;
	char	**env;

	i = 0;
	env = NULL;
	if (!data->i && env_vars)
		while (env_vars[i])
			add_env_val(&env, env_vars[i++]);
	return (env);
}

char		**build_new_env(char **env_vars, t_env *data,
				char **args, int *index)
{
	char	**env;
	char	*new_env;

	env = init_new_env(data, env_vars);
	if (data->u)
		unset_new_env(data, env);
	if (data->i && data->v)
		ft_putendl("#env clearing environ");
	while (args[*index] && ft_strchr(args[*index], '='))
	{
		new_env = ft_strsub(args[*index], 0, ft_strichr(args[*index], '='));
		if (!new_env[0])
		{
			ft_strdel(&new_env);
			ft_printf("env: setenv %s: Invalid var name.\n", args[*index]);
			return (NULL);
		}
		else if (data->v)
			ft_printf("#env setenv:\t%s\n", args[*index]);
		ft_strdel(&new_env);
		add_env_val(&env, args[*index]);
		(*index)++;
	}
	return (env);
}

int			check_is_file(char *path)
{
	struct stat	info;

	if (stat(path, &info) != -1)
		if ((info.st_mode & S_IFMT) != S_IFREG)
			return (0);
	return (1);
}

char		**build_param(t_env *data, char **arg, int *index)
{
	int		i;
	char	**param;

	param = NULL;
	if (data->maj_s && data->string && data->string[0])
		param = ft_strsplit(data->string, ' ');
	while (arg[*index])
	{
		add_env_val(&param, arg[*index]);
		(*index)++;
	}
	data->bin_path = get_bin_path(param, data);
	if (data->bin_path && data->v && param && param[0])
	{
		i = 0;
		ft_printf("#env executing:\t%s\n", data->maj_p
			&& param[0][0] != '/' ? data->bin_path : param[0]);
		while (param[i])
		{
			ft_printf("#env\targ[%d]= '%s'\n", i, param[i]);
			i++;
		}
	}
	return (param);
}
