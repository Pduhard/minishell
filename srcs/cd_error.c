/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 05:44:15 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 05:47:18 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*build_path(char *arg)
{
	char	*pwd;
	char	*tmp;

	if (!(pwd = getcwd(NULL, 0)))
		return (NULL);
	tmp = NULL;
	if (arg && arg[0] != '/')
		tmp = ft_strjoin(pwd, "/");
	ft_strdel(&pwd);
	pwd = ft_strjoin(tmp, arg);
	ft_strdel(&tmp);
	ft_strdel(&arg);
	return (pwd);
}

static char	*build_error(char *path)
{
	struct stat	info;

	if (path)
		;
	if (access(path, F_OK) == -1)
		return ("no such file or directory");
	else if (access(path, R_OK) == -1)
		return ("permission denied");
	else if (lstat(path, &info) == 0 && (info.st_mode & S_IFMT) != S_IFDIR)
		return ("not a directory");
	return ("no such file or dirdfhethectory");
}

static int	cd_err(char *message, char *error, char *name)
{
	if (!error)
		ft_putstr(message);
	else
		ft_printf(message, error, name);
	return (0);
}

static int	end_cd_error(char *new_path, int p, char *arg)
{
	if (chdir(new_path) == -1)
	{
		if (p)
			ft_printf("cd: %s", arg
					? "too many arguments\n" : "missing $OLDPWD value\n");
		else
			ft_printf("cd: %s: %s\n", build_error(new_path), arg);
		ft_strdel(&new_path);
		return (0);
	}
	ft_strdel(&new_path);
	return (1);
}

int			check_cd_error(char **argv, int i, int p, char **env)
{
	char	*new_path;

	new_path = NULL;
	if (argv[i] && argv[i + 1])
		return (cd_err("cd: too many arguments\n", NULL, NULL));
	if (!argv[i] && !p)
	{
		if (!(new_path = find_env_val(env, "HOME=")))
			return (cd_err("cd: no default value (env: $HOME)\n", NULL, NULL));
	}
	else if ((argv[i] && !p) || (!argv[i] && p))
	{
		if (!(new_path = build_path(p
						? find_env_val(env, "OLDPWD=") : ft_strdup(argv[i]))))
			return (cd_err("cd: %s: %s\n", build_error(new_path), argv[i]));
	}
	return (end_cd_error(new_path, p, argv[i]));
}
