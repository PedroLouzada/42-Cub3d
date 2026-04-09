/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:27 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/07 22:06:08 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	round_vtrs(t_vtr *a, t_vtr *b)
{
	a->x = round(a->x);
	a->y = round(a->y);
	b->x = round(b->x);
	b->y = round(b->y);
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
