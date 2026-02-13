#include "cub3d.h"

t_vtr	get_dir(int orientation)
{
	t_vtr	dir;

	dir.x = (orientation == EAST) - (orientation == WEST);
	dir.y = (orientation == SOUTH) - (orientation == NORTH);
	return (dir);
}

double	get_fov(char direction)
{
	if (direction == 'N')
		return (0);
	else if (direction == 'E')
		return (90);
	else if (direction == 'S')
		return (180);
	else if (direction == 'W')
		return (270);
	else
		return (-1);
}

void	rotate(t_player *player, double angle)
{
	player->fov += angle;
	if (player->fov < 0)
		player->fov += 360;
	if (player->fov > 360)
		player->fov -= 360;
}

static void	walk(t_eng *eng, t_player *player)
{
	double		rad;
	const double	speed = 0.25;

	rad = player->fov * (M_PI / 180);
	if (eng->key[K_D])
	{
		player->pos.x += cos(rad) * speed;
		player->pos.y += sin(rad) * speed;
	}
	if (eng->key[K_A])
	{
		player->pos.x -= cos(rad) * speed;
		player->pos.y -= sin(rad) * speed;
	}
	if (eng->key[K_W])
	{
		player->pos.x += cos(rad - M_PI_2) * speed;
		player->pos.y += sin(rad - M_PI_2) * speed;
	}
	if (eng->key[K_S])
	{
		player->pos.x += cos(rad + M_PI_2) * speed;
		player->pos.y += sin(rad + M_PI_2) * speed;
	}
}

static void	movement(t_player *player)
{
	const double	sense = 5;

	if (game()->eng->key[K_LEFT] && !game()->eng->key[K_RIGHT])
		player->rotate(player, sense * -1);
	else if (game()->eng->key[K_RIGHT] && !game()->eng->key[K_LEFT])
		player->rotate(player, sense);
	walk(game()->eng, player);
}

void	p_update(t_obj *obj)
{
	t_player	*player;

	player = (t_player *)obj;
	movement(player);
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
	//player->fov = get_fov(game()->map[level]->direction);
	player->rotate = rotate;
	player->update = p_update;
	return ((t_obj *)player);
}
