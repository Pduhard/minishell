/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env_options.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 02:57:31 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 03:26:54 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**add_unset(t_env *env, char *new_unset)
{
	int		i;
	char	**new_names;

	i = 0;
	while (env->names && env->names[i])
		i++;
	if (!(new_names = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (env->names && env->names[++i])
		new_names[i] = env->names[i];
	i = i == -1 ? 0 : i;
	new_names[i++] = ft_strjoin(new_unset, "=");
	free(new_unset);
	new_names[i] = NULL;
	if (env->names)
		free(env->names);
	return (new_names);
}

static int	invalid_option(char opt, int err)
{
	if (err == 1)
		ft_fdprintf(2, "env: option requires an argument -- %c\n", opt);
	else if (err == 2)
		ft_fdprintf(2, "env: illegal option -- %c\n", opt);
	ft_fdprintf(2, "usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
	ft_fdprintf(2, "\t   [name=value ...] [utility [argument ...]]\n");
	return (0);
}

static int	opt_param(char *options, int i, t_env *env, char *val)
{
	char	**addr;
	int		*opt;

	if (options[i] == 'P')
	{
		opt = &env->maj_p;
		addr = &env->alpath;
	}
	else if (options[i] == 'S')
	{
		opt = &env->maj_s;
		addr = &env->string;
	}
	else
		return (23);
	*addr = val;
	*opt = 1;
	return (1);
}

int			update_option(char *opt, t_env *env, char **argv, int *j)
{
	int		i;

	if ((i = -1) && !opt[0])
		return ((env->i = 1));
	while (opt[++i])
	{
		if (opt[i] == 'i')
			env->i = 1;
		else if (opt[i] == 'v')
			env->v = 1;
		else if ((opt[i] == 'P' || opt[i] == 'S' || opt[i] == 'u')
				&& (!opt[i + 1] && !argv[*j + 1]))
			return (invalid_option(opt[i], 1));
		else if (opt[i] == 'P' || opt[i] == 'S')
			return (opt_param(opt, i, env, opt[i + 1] ? ft_strsub(&opt[i + 1],
					0, ft_strlen(&opt[i + 1])) : ft_strdup(argv[++(*j)])));
		else if (opt[i] == 'u' && (env->u = 1) &&
			(env->names = opt[i + 1] ? add_unset(env,
				ft_strsub(&opt[i + 1], 0, ft_strlen(&opt[i + 1])))
					: add_unset(env, ft_strdup(argv[++(*j)]))))
			return (1);
		else
			return (invalid_option(opt[i], 2));
	}
	return (1);
}
