#include "cub3d.h"

void	compute_perp(t_ray *r)
{
    if (r->side == 0)
        r->perp = r->sDist.x - r->dltDist.x;
    else
        r->perp = r->sDist.y - r->dltDist.y;
}

void	init_ray(t_ray *r, t_obj *obj, int column)
{
	double	cameraX;

	cameraX = 2.0 * column / (double)WIN_WIDTH - 1.0;
	r->dir.x = obj->dir.x + obj->plane.x * cameraX;
	r->dir.y = obj->dir.y + obj->plane.y * cameraX;
	r->map.x = floor(obj->pos.x);
	r->map.y = floor(obj->pos.y);
	r->pos = obj->pos;
	r->dltDist.x = fabs(1 / r->dir.x);
	r->dltDist.y = fabs(1 / r->dir.y);
	r->step.x = (r->dir.x > 0) - (r->dir.x < 0);
	r->step.y = (r->dir.y > 0) - (r->dir.y < 0);
	if (r->dir.x < 0)
		r->sDist.x = (obj->pos.x - r->map.x) * r->dltDist.x;
	else
		r->sDist.x = (r->map.x + 1.0 - obj->pos.x) * r->dltDist.x;
	if (r->dir.y < 0)
		r->sDist.y = (obj->pos.y - r->map.y) * r->dltDist.y;
	else
		r->sDist.y = (r->map.y + 1.0 - obj->pos.y) * r->dltDist.y;
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

void	cast_rays(t_map *m, t_ray *r, t_obj *obj, int type)
{
	int	i;
	char **map;

	map = m->map;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		init_ray(&r[i], obj, i);
		dda(&r[i], map);
		compute_perp(&r[i]);
		if (type == E)
			continue ;
		draw_column(&r[i], i, m->textures);
	}
}
