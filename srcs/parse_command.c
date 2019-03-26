/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_command.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 16:54:00 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 06:41:23 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd			*new_instr(char *instr)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd)))
		|| !(cmd->name = get_argument(instr, &i))
			|| !(cmd->argv = get_instr_arg(instr, &i, cmd->name)))
	{
		if (cmd->name)
			ft_strdel(&cmd->name);
		if (cmd)
			free(cmd);
		return (NULL);
	}
	cmd->next = NULL;
	cmd->bin_path = NULL;
	return (cmd);
}

static t_cmd	*free_all_error(t_cmd *cmd, char **instr, int i)
{
	t_cmd	*next;

	while (instr[i])
		ft_strdel(&instr[i++]);
	free(instr);
	while (cmd)
	{
		next = cmd->next;
		free_command(cmd);
		cmd = next;
	}
	return (NULL);
}

t_cmd			*parse_command(char **line, char **env, char **dir_stack)
{
	t_cmd	*first;
	t_cmd	*curr;
	char	**instr;
	int		i;

	i = 0;
	curr = NULL;
	first = NULL;
	if (!(*line) || !(instr = ft_strsplit(*line, ';')))
		return (NULL);
	while (instr[i])
	{
		replace_dollar_exp(&instr[i], env);
		replace_tilde_exp(&instr[i], env, dir_stack);
		if ((!first && !(first = new_instr(instr[i])))
				|| (curr && !(curr->next = new_instr(instr[i]))))
			return (free_all_error(first, instr, i));
		curr = first->next ? curr->next : first;
		ft_strdel(&instr[i++]);
	}
	free(instr);
	return (first);
}
