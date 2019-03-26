/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_cmd_arg.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 06:38:44 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 06:39:34 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*get_quote_arg(char *instr, int *i, int start, char *name)
{
	char	*next;

	if (!name)
	{
		name = ft_strsub(&instr[*i], 0, start - *i);
		*i = start;
	}
	if (!(next = get_argument(instr, i)))
	{
		ft_strdel(&name);
		return (NULL);
	}
	return (ft_strfjoin(name, next));
}

static int		init_get_arg(char *end, int *i, char *instr)
{
	while (ft_isspace(instr[*i]))
		(*i)++;
	*end = '\0';
	if (instr[*i] == '\'' || instr[*i] == '"')
		*end = instr[(*i)++];
	return (*i - 1);
}

char			*get_argument(char *instr, int *i)
{
	char	end;
	int		start;
	char	*name;

	start = init_get_arg(&end, i, instr);
	while (instr[++start] && ((end && instr[start] != end)
		|| (!end && !ft_isspace(instr[start]))))
		if (!end && (instr[start] == '\'' || instr[start] == '"'))
			return (get_quote_arg(instr, i, start, NULL));
	name = ft_strsub(&instr[*i], 0, start - *i);
	if (end && !instr[start])
	{
		*i = start;
		ft_fdprintf(2, "Missing quote %c\n", end);
		ft_strdel(&name);
		return (NULL);
	}
	*i = end ? start + 1 : start;
	while (ft_isspace(instr[*i]))
		(*i)++;
	if (instr[*i] && ((*i == start + 1 && end) || (*i == start && !end)))
		return (get_quote_arg(instr, i, start, name));
	return (name);
}

int				join_arg(char ***arg, char *to_add)
{
	int		i;
	char	**new_arg;

	i = 0;
	while ((*arg) && (*arg)[i])
		i++;
	if (!(new_arg = (char **)malloc(sizeof(char *) * (i + 2))))
		return (0);
	i = -1;
	while ((*arg) && (*arg)[++i])
		new_arg[i] = (*arg)[i];
	i = i == -1 ? 0 : i;
	new_arg[i++] = to_add;
	new_arg[i] = NULL;
	free(*arg);
	*arg = new_arg;
	return (1);
}

char			**get_instr_arg(char *instr, int *i, char *name)
{
	char	**arg;
	char	*next;
	int		j;

	arg = NULL;
	if (!(arg = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	arg[0] = ft_strdup(name);
	arg[1] = NULL;
	while (instr[*i])
	{
		if (!(next = get_argument(instr, i)))
		{
			j = 0;
			while (arg && arg[j])
				ft_strdel(&arg[j++]);
			if (arg)
				free(arg);
			return (NULL);
		}
		join_arg(&arg, next);
	}
	return (arg);
}
