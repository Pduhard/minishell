/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_echo.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 18:33:29 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 00:01:39 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_echo_option(char **argv, int *i)
{
	int		j;
	int		res;
	int		check;

	check = 0;
	res = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		j = 1;
		while (argv[*i][j])
		{
			check = 1;
			if (argv[*i][j] != 'n')
				return (res);
			res = 1;
			j++;
		}
		if (!check)
			return (res);
		(*i)++;
	}
	return (res);
}

void		ft_echo(t_cmd *cmd)
{
	int		i;
	int		n;
	char	*str;
	char	*tmp;

	i = 1;
	n = get_echo_option(cmd->argv, &i);
	str = NULL;
	while (cmd->argv[i])
	{
		if (!str)
			str = ft_strdup(cmd->argv[i]);
		else
		{
			str = ft_strfjoin(str, ft_strdup(" "));
			tmp = ft_strjoin(str, cmd->argv[i]);
			ft_strdel(&str);
			str = tmp;
		}
		i++;
	}
	if (n)
		str = ft_strfjoin(str, ft_strdup("\x1b[47;38;2;0;0;0;1m%\x1b[0m"));
	ft_putendl(str);
	ft_strdel(&str);
}
