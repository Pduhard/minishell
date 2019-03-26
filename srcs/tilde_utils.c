/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tilde_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 06:06:59 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 06:09:31 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_tilde_number(char *str)
{
	int		check;

	check = 0;
	while (ft_isdigit(*str))
	{
		check = 1;
		str++;
	}
	if (check && (!*str || *str == '/'))
		return (1);
	return (0);
}
