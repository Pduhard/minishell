/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 23:31:22 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 10:26:05 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_valid_env_var(char *var_name)
{
	if (!ft_isalpha(*var_name))
		return (0);
	while (*var_name)
	{
		if (!ft_isalnum(*var_name) && *var_name != '_')
			return (0);
		var_name++;
	}
	return (1);
}

static int	check_number_argument(char **argv, char **to_del)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 3)
	{
		if (to_del)
			ft_strdel(to_del);
		ft_printf("setenv: Too many arguments.\n%s"
			, "usage: setenv <var_name> <value>\n");
		return (0);
	}
	return (1);
}

static int	check_validity(char **argv, int i)
{
	if (!is_valid_env_var(argv[i]))
	{
		if (ft_isalpha(argv[i][0]))
			ft_printf("setenv: Variable name must %s\n"
				, "only contain alphanumeric characters.");
		else
			ft_printf("setenv: Variable name must begin with a letter.\n");
		return (0);
	}
	if (!check_number_argument(argv, NULL))
		return (0);
	return (1);
}

static void	set_update_env(char **env, char **argv, char *tmp, int i)
{
	char	*new_path;

	new_path = ft_strjoin(argv[i], "=");
	update_env_val(env, new_path, argv[i + 1]);
	ft_strdel(&tmp);
	ft_strdel(&new_path);
}

int			ft_setenv(t_cmd *cmd, char ***env)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!cmd->argv[i])
		ft_env(cmd, *env);
	else if (!cmd->argv[i][0])
		return (ft_printf("setenv: Variable name must at least contain %s\n"
			, "one character.") - 62);
	else if ((tmp = find_env_val(*env, cmd->argv[i])))
	{
		if (!check_number_argument(cmd->argv, &tmp))
			return (-1);
		set_update_env(*env, cmd->argv, tmp, i);
	}
	else
	{
		if (!check_validity(cmd->argv, i))
			return (-1);
		tmp = ft_strjoin(cmd->argv[i++], "=");
		tmp = ft_strfjoin(tmp, ft_strdup(cmd->argv[i]));
		add_env_val(env, tmp);
		ft_strdel(&tmp);
	}
	return (1);
}
