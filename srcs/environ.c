/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   environ.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 07:42:36 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 04:43:05 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_env_val(char **env, char *var_name)
{
	int		len;
	int		i;

	len = ft_strlen(var_name);
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], var_name, len))
		i++;
	if (!env || !env[i])
		return (NULL);
	return (ft_strsub(env[i], len, ft_strlen(env[i]) - len));
}

void	update_env_val(char **env, char *var_name, char *new_val)
{
	int		len;
	int		i;
	char	*tmp;

	len = ft_strlen(var_name);
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], var_name, len))
		i++;
	if (!env || !env[i])
		return ;
	tmp = ft_strsub(env[i], 0, len);
	ft_strdel(&env[i]);
	env[i] = ft_strjoin(tmp, new_val);
	ft_strdel(&tmp);
}

void	add_env_val(char ***env, char *new_env_val)
{
	int		i;
	char	**new_env;

	i = 0;
	while (*env && (*env)[i])
		i++;
	if (!(new_env = (char **)malloc(sizeof(char *) * (i + 2))))
		return ;
	i = -1;
	while (*env && (*env)[++i])
		new_env[i] = (*env)[i];
	i = i == -1 ? 0 : i;
	new_env[i++] = ft_strdup(new_env_val);
	new_env[i] = NULL;
	free(*env);
	*env = new_env;
}

void	remove_env_var(char **var, char **env, int start)
{
	int		i;
	int		len;
	int		j;

	i = start;
	while (var && var[i])
	{
		j = 0;
		len = ft_strlen(var[i]);
		while (env && env[j] && env[j + 1])
		{
			if (!ft_strncmp(env[j], var[i], len))
				ft_strswap(&env[j], &env[j + 1]);
			j++;
		}
		if (env && env[j] && !ft_strncmp(env[j], var[i], len))
			ft_strdel(&env[j]);
		i++;
	}
}

char	**get_environ(void)
{
	extern char	**environ;
	int			len;
	char		**env;

	len = 0;
	while (environ[len])
		len++;
	if (!(env = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	len = -1;
	while (environ[++len])
		env[len] = ft_strdup(environ[len]);
	env[len] = NULL;
	return (env);
}
