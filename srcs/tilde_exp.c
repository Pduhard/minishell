/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tilde_exp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 18:33:07 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 05:16:40 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	replace_tilde(char *tilde_val, char **line, int i, int len)
{
	char	*new_line;

	if (!tilde_val)
		return ;
	new_line = ft_strsub(*line, 0, i);
	new_line = ft_strfjoin(new_line, tilde_val);
	new_line = ft_strfjoin(new_line,
		ft_strsub(*line, i + len, ft_strlen(*line) - (i + len)));
	ft_strdel(line);
	*line = new_line;
}

static char	*find_user(char *str, int *len)
{
	char			*name;
	DIR				*users_dir;
	struct dirent	*file;

	if (!(users_dir = opendir("/Users")))
		return (NULL);
	*len = 0;
	while (!ft_isspace(str[*len]) && str[*len] && str[*len] != '/')
		(*len)++;
	name = ft_strsub(str, 0, *len);
	while ((file = readdir(users_dir)))
	{
		if (!ft_strcmp(name, file->d_name))
		{
			closedir(users_dir);
			return (ft_strfjoin(ft_strdup("/Users/"), name));
		}
	}
	closedir(users_dir);
	ft_strdel(&name);
	return (NULL);
}

static char	*find_dir_in_stack(int nb, int way, char **dir_stack, int *len)
{
	int		i;

	i = 0;
	*len = ft_intlen(nb);
	while (dir_stack[i])
		i++;
	if (nb >= i)
		return (NULL);
	if (way == 1)
		i = 0;
	else
		nb++;
	while (nb--)
		i += way;
	return (ft_strdup(dir_stack[i]));
}

static int	manage_search_way(char **line, int i, char **dir_stack, char **env)
{
	int		len;

	if ((*line)[i + 1] == '-')
	{
		if (is_tilde_number(&(*line)[i + 2]))
			replace_tilde(find_dir_in_stack(ft_atoi(&(*line)[i + 2]),
				-1, dir_stack, &len), line, i, len + 2);
		else if (!(*line)[i + 2] || (*line)[i + 2] == '/')
			replace_tilde(find_env_val(env, "OLDPWD="), line, i, 2);
		return (1);
	}
	else if ((*line)[i + 1] == '+')
	{
		if (is_tilde_number(&(*line)[i + 2]))
			replace_tilde(find_dir_in_stack(ft_atoi(&(*line)[i + 2]), 1,
				dir_stack, &len), line, i, len + 2);
		else if (!(*line)[i + 2] || (*line)[i + 2] == '/')
			replace_tilde(find_env_val(env, "PWD="), line, i, 2);
		return (1);
	}
	return (0);
}

void		replace_tilde_exp(char **line, char **env, char **dir_stack)
{
	int		i;
	int		len;

	i = 0;
	while ((*line)[i] && dir_stack)
	{
		if ((*line)[i] == '~' && (i == 0 || ft_isspace((*line)[i - 1])))
		{
			if (manage_search_way(line, i, dir_stack, env))
				;
			else if (is_tilde_number(&(*line)[i + 1]))
				replace_tilde(find_dir_in_stack(ft_atoi(&(*line)[i + 1]), -1,
					dir_stack, &len), line, i, len + 2);
			else if (ft_isspace((*line)[i + 1]) || !(*line)[i + 1]
				|| (*line)[i + 1] == '/')
				replace_tilde(find_env_val(env, "HOME="), line, i, 1);
			else
				replace_tilde(find_user(&(*line)[i + 1], &len),
					line, i, len + 1);
		}
		i++;
	}
}
