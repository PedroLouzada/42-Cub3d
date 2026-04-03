#include "cub3d.h"

bool	e_sees_p(t_vtr pos, t_map *map, bool memory)
{
	t_enemy		*e;
	t_player	*p;
	t_vtr		diff;

	e = (t_enemy *)map->objs[E];
	p = (t_player *)map->objs[P];
	if (((int)pos.x == (int)p->pos.x && (int)pos.y == (int)p->pos.y) || memory)
	{
		diff.x = p->pos.x - e->pos.x;
		diff.y = p->pos.y - e->pos.y;
		e->chase = true;
		e->angle = atan2(diff.y, diff.x);
		set_e_orientation(e);
		return (true);
	}
	return (false);
}

void	e_dda(t_ray *r, t_map *map)
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
		if (e_sees_p(r->map, map, false))
			return ;
		if (map->map[(int)r->map.y][(int)r->map.x] != '0')
			return ;
	}
}

void	enemy_los(t_enemy *e, t_map *map)
{
	int		i;
	bool	had_los;

	had_los = e->chase;
	e->chase = false;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		init_ray(&e->ray[i], (t_obj *)e, i);
		e_dda(&e->ray[i], map);
		if (e->ray[i].side == 0)
			e->ray[i].perp = e->ray[i].sDist.x - e->ray[i].dltDist.x;
		else
			e->ray[i].perp = e->ray[i].sDist.y - e->ray[i].dltDist.y;
	}
	if (had_los && e_timer(false, MEMORY) < 10.0)
		e_sees_p(e->pos, map, true);
	else if (had_los)
		e_timer(true, MEMORY);
}
