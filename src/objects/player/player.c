#include "cub3d.h"

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
	double		angle;
	const int	speed = 1;

	angle = player->fov * (M_PI / 180);
	if (eng->key[K_W])
	{
		player->pos.x += cos(angle) * speed;
		player->pos.y += sin(angle) * speed;
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

t_obj	*create_player(int level)
{
	int 		*pos;
	t_player	*new_player;

	new_player = ft_calloc(1, sizeof(t_player));
	if (!new_player)
		return (NULL);
	new_player->fov = get_fov(game()->map[level]->direction);
	new_player->rotate = rotate;
	new_player->update = p_update;
	get_pos(pos, game()->map[level]->map, 1);
	new_player->pos.x = pos[0];
	new_player->pos.x = pos[1];
	fprintf(stderr, "X: %d", new_player->pos.x);
	fprintf(stderr, "Y: %d", new_player->pos.y);
	exit (0);
	return ((t_obj *)new_player);
}
