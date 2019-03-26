/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dir_stack.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 16:54:08 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 06:03:55 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_dirs(char **env, char **dir_stack)
{
	int		i;
	char	*tilde;
	int		len;
	char	*smooth;

	i = 0;
	tilde = find_env_val(env, "HOME=");
	len = ft_strlen(tilde);
	while (dir_stack && dir_stack[i])
		i++;
	while (dir_stack && --i > -1)
	{
		if (!ft_strncmp(dir_stack[i], tilde, len))
			smooth = ft_strfjoin(ft_strdup("~"), ft_strsub(dir_stack[i],
				len, ft_strlen(dir_stack[i]) - len));
		else
			smooth = ft_strdup(dir_stack[i]);
		ft_putstr(smooth);
		ft_strdel(&smooth);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
	ft_strdel(&tilde);
}

void		add_dir_to_stack(char ***dir_stack, char *new_path)
{
	int		i;
	char	**new_stack;

	i = 0;
	while (*dir_stack && (*dir_stack)[i] && (*dir_stack)[i + 1])
	{
		if (!ft_strcmp((*dir_stack)[i], new_path))
			ft_strswap(&(*dir_stack)[i], &(*dir_stack)[i + 1]);
		i++;
	}
	if (*dir_stack && !ft_strcmp((*dir_stack)[i], new_path))
		return ;
	if (!(new_stack = (char **)malloc(sizeof(char *) * (i + 3))))
		return ;
	i = -1;
	while (*dir_stack && (*dir_stack)[++i])
		new_stack[i] = (*dir_stack)[i];
	i = i == -1 ? 0 : i;
	new_stack[i++] = ft_strdup(new_path);
	new_stack[i] = NULL;
	free(*dir_stack);
	*dir_stack = new_stack;
}
