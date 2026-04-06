#include "cub3d.h"

double	e_timer(bool reset, int timer)
{
	static double	start[3];

	if (reset)
		start[timer] = 0;
	if (!start[timer])
		start[timer] = get_time();
	return (get_time() - start[timer]);
}

bool	e_is_stuck(t_enemy *e, t_vtr prev, double prev_angle)
{
	if ((int)prev.x == (int)e->pos.x && (int)prev.y == (int)e->pos.y
	&& prev_angle == e->angle)
		return (true);
	return (false);
}

bool	e_hits_player(t_enemy *e, t_player *p, t_map *map)
{
	t_vtr walk;
	t_vtr	diff;
	float speed;

	speed = 2.0;
	walk.x = e->pos.x + cos(e->angle) * speed * game()->eng.dt;
	walk.y = e->pos.y + sin(e->angle) * speed * game()->eng.dt;
	if (in_bounds(map->map, (int)e->pos.y, (int)walk.x)
		&& map->map[(int)e->pos.y][(int)walk.x] == '0')
		e->pos.x = walk.x;
	if (in_bounds(map->map, (int)walk.y, (int)e->pos.x)
		&& map->map[(int)walk.y][(int)e->pos.x] == '0')
		e->pos.y = walk.y;
	diff.x = e->pos.x - p->pos.x;
	diff.y = e->pos.y - p->pos.y;
	if (diff.x * diff.x + diff.y * diff.y <= RADIUS * RADIUS)
		return (true);
	return (false);
}

void	e_update(t_obj *this, t_map *map)
{
	t_enemy		*e;
	t_player	*p;
	static t_vtr	prev;
	static double	prev_angle;

	if (!game()->eng.current_map)
		return ;
	e = (t_enemy *)this;
	p = (t_player *)map->objs[P];
	if (e_hits_player(e, p, map))
	{
		p->lives--;
		if (p->lives <= 0)
			exit_game("Game Over\n");
		e->chase = false;
		e->pos = spawn(map, '0');
		e_timer(true, RESPAWN);
		e_timer(true, STUCK);
	}
	else if ((e_timer(false, STUCK) > 10.0 && e_is_stuck(e, prev, prev_angle))
	|| e_timer(false, RESPAWN) > 120.0)
	{
		e->chase = false;
		e->pos = spawn(map, '0');
		e_timer(true, RESPAWN);
		e_timer(true, STUCK);
	}
	prev = e->pos;
	prev_angle = e->angle;
	enemy_los(e, map);
	if (e->chase)
		e_chase(e, map);
	else
		e_walk(e, map);
	if (!e_is_stuck(e, prev, prev_angle))
		e_timer(true, STUCK);
	e->frame++;
}

void	*enemy_get_texture(t_obj *this, double dir)
{
	t_enemy	*e;
	(void)dir;

	e = (t_enemy *)this;
	return ((void *)e->textures[e->frame % 6]);
}

t_obj	*create_enemy(t_vtr pos)
{
	t_enemy *e;
	int		i;
	t_imgs	*paths[6];

	paths[0] = game()->mlx->img[23];
	paths[1] = game()->mlx->img[24];
	paths[2] = game()->mlx->img[25];
	paths[3] = game()->mlx->img[26];
	paths[4] = game()->mlx->img[27];
	paths[5] = game()->mlx->img[28];
	e = ft_calloc(1, sizeof(t_enemy));
	if (!e)
		return (NULL);
	e->ray = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray));
	if (!e->ray)
	{
		free(e);
		return (NULL);
	}
	i = -1;
	while (++i < 6)
		e->textures[i] = paths[i];
	e->pos = pos;
	e->update = e_update;
	e->get_texture = enemy_get_texture;
 	e->chase = false;
	e->frame = 0;
	e->angle = pick_rand(pick_rand(M_PI_2, 0), pick_rand(M_PI, 3 * M_PI_2));
	set_e_orientation(e);
	return ((t_obj *)e);
}
