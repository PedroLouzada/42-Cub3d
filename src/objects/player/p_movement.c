#include "cub3d.h"

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

void	set_p_orientation(t_player *p)
{
	p->dir.x = cos(p->angle);
	p->dir.y = sin(p->angle);
	p->plane.x = -p->dir.y * FOV;
	p->plane.y = p->dir.x * FOV;
}

void	p_rotate(t_eng *eng, t_player *p)
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
	set_p_orientation(p);
}

void	p_walk(t_eng *eng, t_player *p, t_map *map)
{
	t_vtr	walk;
	double	speed;
	double	walk_angle;

	speed = 1.0;
	if (eng->key[SHIFT])
		speed *= 2.0;
	walk_angle = p->angle;
	handle_angle(eng, p, &walk_angle, &speed);
	walk.x = p->pos.x + cos(walk_angle) * speed * eng->dt;
	walk.y = p->pos.y + sin(walk_angle) * speed * eng->dt;
	if (map->map[(int)p->pos.y][(int)walk.x] == '0')
		p->pos.x = walk.x;
	if (map->map[(int)walk.y][(int)p->pos.x] == '0')
		p->pos.y = walk.y;
}
