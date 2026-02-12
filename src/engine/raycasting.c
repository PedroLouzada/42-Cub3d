#include "cub3d.h"

void	compute_perp(t_ray *r)
{
    if (r->side == 0)
        r->perp = r->sDist.x - r->dltDist.x;
    else
        r->perp = r->sDist.y - r->dltDist.y;
}

void	init_ray(t_ray *r, t_player *p, int column)
{
	double	cameraX;

	cameraX = 2.0 * column / (double)WIN_WIDTH - 1.0;
	r->dir.x = p->dir.x + p->plane.x * cameraX;
	r->dir.y = p->dir.y + p->plane.y * cameraX;
	r->map.x = floor(p->pos.x);
	r->map.y = floor(p->pos.y);
	r->dltDist.x = fabs(1 / r->dir.x);
	r->dltDist.y = fabs(1 / r->dir.y);
	r->step.x = (r->dir.x > 0) - (r->dir.x < 0);
	r->step.y = (r->dir.y > 0) - (r->dir.y < 0);
	if (r->dir.x < 0)
		r->sDist.x = (p->pos.x - r->map.x) * r->dltDist.x;
	else
		r->sDist.x = (r->map.x + 1.0 - p->pos.x) * r->dltDist.x;
	if (r->dir.y < 0)
		r->sDist.y = (p->pos.y - r->map.y) * r->dltDist.y;
	else
		r->sDist.y = (r->map.y + 1.0 - p->pos.y) * r->dltDist.y;
}

void	dda(t_ray *r, t_str *map)
{
	while (1)
	{
		if (r->sDist.x < r->sDist.y)
		{
			r->sDist.x += r->dltDist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->sDist.y += r->dltDist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (map[(int)r->map.y][(int)r->map.x] == '1')
			break ;
	}
}

void	cast_rays(t_map *map, t_player *p)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		init_ray(&map->rays[i], p, i);
		dda(&map->rays[i], map->map);
		compute_perp(&map->rays[i]);
		draw_column(&map->rays[i], i);
	}
}
