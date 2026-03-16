#include "cub3d.h"

void	set_orientation(t_player *p)
{
	p->dir.x = cos(p->angle);
	p->dir.y = sin(p->angle);
	p->plane.x = -p->dir.y * FOV;
	p->plane.y = p->dir.x * FOV;
}

static void	rotate(t_eng *eng, t_player *p)
{
	double	speed;

	speed = 1.0;
	if (eng->key[K_LEFT] && !eng->key[K_RIGHT])
		p->angle -= speed * eng->dt;
	else if (eng->key[K_RIGHT] && !eng->key[K_LEFT])
		p->angle += speed * eng->dt;
	if (p->angle < 0)
		p->angle = 2 * M_PI;
	if (p->angle > 2 * M_PI)
		p->angle = 0;
	set_orientation(p);
}

void	handle_angle(t_eng *eng, t_player *p, double *angle, double *speed)
{
	if (eng->key[K_D])
		*angle = p->angle + M_PI_2;
	if (eng->key[K_S])
		*angle = p->angle + M_PI;
	if (eng->key[K_A])
		*angle = p->angle - M_PI_2;
	if (eng->key[K_W] && eng->key[K_D])
		*angle = p->angle + M_PI_4;
	if (eng->key[K_W] && eng->key[K_A])
		*angle = p->angle - M_PI_4;
	if (eng->key[K_S] && eng->key[K_D])
		*angle = p->angle + 3 * M_PI_4;
	if (eng->key[K_S] && eng->key[K_A])
		*angle = p->angle - 3 * M_PI_4;
	if ((eng->key[K_W] && eng->key[K_D]) || (eng->key[K_W] && eng->key[K_A])
		|| (eng->key[K_S] && eng->key[K_D]) || (eng->key[K_S] && eng->key[K_A]))
		*speed *= 1.2;
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'P');
}

void	walk(t_eng *eng, t_player *p, t_map *map)
{
	t_vtr	walk;
	double	speed;
	double	walk_angle;

	speed = 1.5;
	if (eng->key[SHIFT] && p->stamina >= 10)
		speed *= 2.0;
	else if (eng->key[CTRL])
		speed /= 2.0;
	walk_angle = p->angle;
	handle_angle(eng, p, &walk_angle, &speed);
	walk.x = p->pos.x + cos(walk_angle) * speed * eng->dt;
	walk.y = p->pos.y + sin(walk_angle) * speed * eng->dt;
	if (map->map[(int)p->pos.y][(int)walk.x] == '0'
		|| map->map[(int)p->pos.y][(int)walk.x] == 'd'
		|| is_player(map->map[(int)p->pos.y][(int)walk.x]))
		p->pos.x = walk.x;
	if (map->map[(int)walk.y][(int)p->pos.x] == '0'
		|| map->map[(int)walk.y][(int)p->pos.x] == 'd'
		|| is_player(map->map[(int)walk.y][(int)p->pos.x]))
		p->pos.y = walk.y;
}

void	p_update(t_obj *obj, t_map *map)
{
	t_player	*p;

	p = (t_player *)obj;
	if (game()->eng.key[K_LEFT] || game()->eng.key[K_RIGHT])
		rotate(&game()->eng, p);
	if (game()->eng.key[K_W] || game()->eng.key[K_S] || game()->eng.key[K_A]
		|| game()->eng.key[K_D])
		walk(&game()->eng, p, map);
	if (game()->eng.key[K_F] == true && p->battery > 0)
		p->battery -= 5 * game()->eng.dt;
	else if (game()->eng.key[K_F] == false && p->battery < 100)
		p->battery += 4 * game()->eng.dt;
	else if (p->battery <= 0 && game()->eng.key[K_F] == true)
		game()->eng.key[K_F] = false;
	if (game()->eng.key[SHIFT] && p->stamina >= 0)
		p->stamina -= 30 * game()->eng.dt;
	else if (p->stamina < 100)
		p->stamina += 20 * game()->eng.dt;
	if (game()->eng.key[K_E] && !game()->eng.door)
	{
		interact_door(p, map, map->rays[P]);
		game()->eng.door = true;
	}
	if (!game()->eng.key[K_E])
		game()->eng.door = false;
}

double	get_angle(char dir)
{
	if (dir == 'E')
		return (0);
	if (dir == 'N')
		return (M_PI_2);
	if (dir == 'W')
		return (M_PI);
	if (dir == 'S')
		return (3 * M_PI_2);
	return (-1);
}

t_obj	*create_player(t_vtr pos)
{
	t_player	*p;
	static int	i;

	p = ft_calloc(1, sizeof(t_player));
	if (!p)
		return (NULL);
	p->lives = 3;
	p->pos = pos;
	p->battery = 100;
	p->level = i++;
	p->stamina = 100.00;
	p->update = p_update;
	if (p->level)
		p->angle = pick_rand(pick_rand(M_PI_2, 0), pick_rand(M_PI, 3 * M_PI_2));
	else
		p->angle = get_angle(game()->map[0]->direction);
	set_orientation(p);
	return ((t_obj *)p);
}
