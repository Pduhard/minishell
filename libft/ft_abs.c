/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_abs.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 09:45:04 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/27 09:45:28 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int n)
{
	return (n < 0 ? -n : n);
}