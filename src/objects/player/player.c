#include "cub3d.h"

t_vtr	get_dir(int orientation)
{
	t_vtr	dir;

	dir.x = (orientation == EAST) - (orientation == WEST);
	dir.y = (orientation == SOUTH) - (orientation == NORTH);
	return (dir);
}

double	get_angle(double x, double y)
{
	if (!x && !y)
		return (0);
	if (x && !y)
		return (90);
	if (x && y)
		return (180);
	if (!x && y)
		return (270);
	return (-1);
}

void	rotate(t_player *player, double sense)
{
	double	rad;

	player->angle += sense;
	if (player->angle < 0)
		player->angle += 360;
	if (player->angle > 360)
		player->angle -= 360;
	rad = player->angle * M_PI / 180;
	player->dir.x = cos(rad);
	player->dir.y = sin(rad);
	player->plane.x = -player->dir.y * FOV;
	player->plane.y = player->dir.x * FOV;
}

static void	walk(t_eng *eng, t_player *player, t_str *map)
{
	double	rad;
	double	speed;

	speed = 0.026;
	if (eng->key[SHIFT])
		speed *= 1.5;
	rad = player->angle * (M_PI / 180);
	if (eng->key[K_W])
	{
		player->pos.x += cos(rad) * speed;
		player->pos.y += sin(rad) * speed;
	}
	if (eng->key[K_S])
	{
		player->pos.x -= cos(rad) * speed;
		player->pos.y -= sin(rad) * speed;
	}
	if (eng->key[K_A])
	{
		player->pos.x += cos(rad - M_PI_2) * speed;
		player->pos.y += sin(rad - M_PI_2) * speed;
	}
	if (eng->key[K_D])
	{
		player->pos.x += cos(rad + M_PI_2) * speed;
		player->pos.y += sin(rad + M_PI_2) * speed;
	}
}

static void	movement(t_player *player, t_str *map)
{
	const double	sense = 2.5;

	if (game()->eng->key[K_LEFT] && !game()->eng->key[K_RIGHT])
		player->rotate(player, sense * -1);
	else if (game()->eng->key[K_RIGHT] && !game()->eng->key[K_LEFT])
		player->rotate(player, sense);
	walk(game()->eng, player, map);
}

void	p_update(t_obj *obj, t_map *map)
{
	t_player	*player;

	player = (t_player *)obj;
	movement(player, map->map);
}

t_obj	*create_player(t_vtr pos, int level)
{
	t_player	*player;

	(void)level;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->lives = 3;
	player->pos = pos;
	player->dir = get_dir(pick_range(NORTH, SOUTH));
	player->plane.x = -player->dir.y * FOV;
	player->plane.y = player->dir.x * FOV;
	player->angle = get_angle(player->dir.x, player->dir.y);
	player->rotate = rotate;
	player->update = p_update;
	return ((t_obj *)player);
}
