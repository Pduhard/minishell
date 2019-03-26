/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 15:17:11 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 05:46:23 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_cd_options(char **argv, int *i)
{
	int		j;

	while (argv[*i] && argv[*i][0] == '-')
	{
		j = 1;
		while (argv[*i][j] && (argv[*i][j] == 'L' || argv[*i][j] == 'P'))
			j++;
		if (argv[*i][j])
			return (0);
		if (!argv[*i][j] && j == 1)
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

static void	update_env_pwd(char **env, char *new_path, t_shell *shell)
{
	char	*tmp;

	if (shell && (tmp = find_env_val(env, "PWD=")))
	{
		update_env_val(env, "OLDPWD=", tmp);
		ft_strdel(&tmp);
	}
	update_env_val(env, "PWD=", new_path);
}

int			ft_cd(t_cmd *cmd, char **env, t_shell *shell)
{
	int		p;
	int		i;
	char	*new_path;

	i = 1;
	p = get_cd_options(cmd->argv, &i);
	if (!check_cd_error(cmd->argv, i, p, env))
		return (-1);
	new_path = getcwd(NULL, 0);
	update_env_pwd(env, new_path, shell);
	add_dir_to_stack(&shell->dir_stack, new_path);
	ft_strdel(&new_path);
	return (1);
}
