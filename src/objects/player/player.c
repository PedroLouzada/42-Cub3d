#include "cub3d.h"

static void	set_orientation(t_player *p)
{
	p->dir.x = cos(p->angle);
	p->dir.y = sin(p->angle);
	p->plane.x = -p->dir.y * FOV;
	p->plane.y = p->dir.x * FOV;
}

static void	rotate(t_eng *eng, t_player *p)
{
	double	rotSpeed;

	rotSpeed = 0.03;
	if (eng->key[K_LEFT] && !eng->key[K_RIGHT])
		p->angle -= rotSpeed;
	else if (eng->key[K_RIGHT] && !eng->key[K_LEFT])
		p->angle += rotSpeed;
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

void	walk(t_eng *eng, t_player *p, t_map *map)
{
	t_vtr	walk;
	double	speed;
	double	walkAngle;

	speed = 0.045;
	if (eng->key[SHIFT])
		speed *= 2.0;
	walkAngle = p->angle;
	handle_angle(eng, p, &walkAngle, &speed);
	walk.x = p->pos.x + cos(walkAngle) * speed;
	walk.y = p->pos.y + sin(walkAngle) * speed;
	if (map->map[(int)p->pos.y][(int)walk.x] == '0')
		p->pos.x = walk.x;
	if (map->map[(int)walk.y][(int)p->pos.x] == '0')
		p->pos.y = walk.y;
}

void	p_update(t_obj *obj, t_map *map)
{
	t_player	*p;

	p = (t_player *)obj;
	if (game()->eng->key[K_LEFT] || game()->eng->key[K_RIGHT])
		rotate(game()->eng, p);
	if (game()->eng->key[K_W] || game()->eng->key[K_S]
	|| game()->eng->key[K_A] || game()->eng->key[K_D])
		walk(game()->eng, p, map);
	if (game()->eng->key[K_F] == true)
		p->battery -= 0.1;
	if (game()->eng->key[K_F] == false && p->battery < 100)
		p->battery += 0.05;
}

t_obj	*create_player(t_vtr pos)
{
	t_player	*p;

	p = ft_calloc(1, sizeof(t_player));
	if (!p)
		return (NULL);
	p->lives = 3;
	p->pos = pos;
	p->battery = 100;
	p->update = p_update;
	p->angle = pick_rand(pick_rand(M_PI_2, 0), pick_rand(M_PI, 3 * M_PI_2));
	set_orientation(p);
	return ((t_obj *)p);
}
