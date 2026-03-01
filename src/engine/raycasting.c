#include "cub3d.h"

void	init_ray(t_ray *r, t_obj *obj, int column)
{
	double	camera_x;

	camera_x = 2.0 * column / (double)WIN_WIDTH - 1.0;
	r->dir.x = obj->dir.x + obj->plane.x * camera_x;
	r->dir.y = obj->dir.y + obj->plane.y * camera_x;
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

void	dda(t_ray *r, t_map *map)
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
		if (map->map[(int)r->map.y][(int)r->map.x] == '1')
			break ;
	}
}

void	reduced_ray(int *array)
{
	int			i;
	t_ray		*r;
	const int	end = array[3];
	t_map		*map;

	map = game()->map[array[0]];
	i = array[2] - 1;
	r = map->rays[array[1]];
	while (++i < end)
	{
		init_ray(&r[i], map->objs[array[1]], i);
		dda(&r[i], map);
		if (r[i].side == 0)
			r[i].perp = r[i].sDist.x - r[i].dltDist.x;
		else
			r[i].perp = r[i].sDist.y - r[i].dltDist.y;
		if (array[1] == E)
			continue ;
		draw_column(&r[i], i, map->textures);
	}
}

void	cast_rays(int map, int type)
{
	int const	args[4][4] = {
	{map, type, 0, 480},
	{map, type, 480, 960},
	{map, type, 960, 1440},
	{map, type, 1440, 1920},
	};
	t_thread	*pool;

	pool = game()->eng->pool;
	pool->deploy(pool, (void *)reduced_ray, (void *)args[0]);
	pool->deploy(pool, (void *)reduced_ray, (void *)args[1]);
	pool->deploy(pool, (void *)reduced_ray, (void *)args[2]);
	pool->deploy(pool, (void *)reduced_ray, (void *)args[3]);
	pool->wait(pool, 4);
}
