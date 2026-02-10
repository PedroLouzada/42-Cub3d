#include "cub3d.h"

void	round_vtrs(t_vtr *a, t_vtr *b)
{
	a->x = round(a->x);
	a->y = round(a->y);
	b->x = round(b->x);
	b->y = round(b->y);
}

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
