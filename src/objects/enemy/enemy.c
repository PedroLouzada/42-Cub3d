#include "cub3d.h"

static void	set_orientation(t_enemy *e)
{
	e->dir.x = cos(e->angle);
	e->dir.y = sin(e->angle);
	e->plane.x = -e->dir.y * FOV;
	e->plane.y = e->dir.x * FOV;
}

static void	rotate(t_enemy *e, double speed)
{
	e->angle += speed * game()->eng->dt;
	if (e->angle < 0)
		e->angle = 2 * M_PI;
	if (e->angle > 2 * M_PI)
		e->angle = 0;
	set_orientation(e);
}

static void	walk(t_enemy *e, t_map *map)
{
	t_vtr	walk;
	double	speed;

	speed = 2.0;
	walk.x = e->pos.x + cos(e->angle) * speed * game()->eng->dt;
	walk.y = e->pos.y + sin(e->angle) * speed * game()->eng->dt;
	if (map->map[(int)e->pos.y][(int)walk.x] == '0')
		e->pos.x = walk.x;
	if (map->map[(int)walk.y][(int)e->pos.x] == '0')
		e->pos.y = walk.y;
	if (map->map[(int)walk.y][(int)walk.x] == '1')
		rotate(e, speed);
}

void	e_update(t_obj *this, t_map *map)
{
	t_enemy		*e;
	t_player	*p;

	e = (t_enemy *)this;
	p = (t_player *)map->objs[P];
	if ((int)e->pos.x == (int)p->pos.x && (int)e->pos.y == (int)p->pos.y)
		e->pos = spawn(map, '0');
	walk(e, map);
}

t_obj	*create_enemy(t_vtr pos)
{
	t_enemy *e;

	e = ft_calloc(1, sizeof(t_enemy));
	if (!e)
		return (NULL);
	e->pos = pos;
	e->update = e_update;
	// e->get_texture = g_texture;
	e->angle = pick_rand(pick_rand(M_PI_2, 0), pick_rand(M_PI, 3 * M_PI_2));
	set_orientation(e);
	return ((t_obj *)e);
}
