/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dolar_exp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 18:33:00 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 04:42:45 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_val(char **env, char *str)
{
	int		len;
	int		i;
	char	*name;

	len = 0;
	i = 0;
	while (ft_isalnum(str[len]))
		len++;
	name = ft_strsub(str, 0, len);
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], len) && ft_strichr(env[i], '=') == len)
		{
			ft_strdel(&name);
			return (ft_strsub(env[i], len + 1, ft_strlen(env[i]) - len - 1));
		}
		i++;
	}
	ft_strdel(&name);
	return (ft_strdup(""));
}

void		replace_var(char **line, int i, char *var)
{
	char	*tmp;
	char	*next;

	tmp = ft_strsub(*line, 0, i++);
	tmp = ft_strfjoin(tmp, var);
	while (ft_isalnum((*line)[i]))
		i++;
	next = ft_strsub(*line, i, ft_strlen(*line) - i);
	ft_strdel(line);
	*line = ft_strfjoin(tmp, next);
}

void		replace_dollar_exp(char **line, char **env)
{
	char	*var;
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (i == 0 || (*line)[i - 1] != '\\')
			&& !ft_isspace((*line)[i + 1]) && (*line)[i + 1])
		{
			var = get_env_val(env, &(*line)[i + 1]);
			replace_var(line, i, var);
			i--;
		}
		i++;
	}
}
