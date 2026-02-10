#include "cub3d.h"

t_vtr	get_dir(int orientation)
{
	t_vtr	dir;

	dir.x = (orientation == EAST) - (orientation == WEST);
	dir.y = (orientation == SOUTH) - (orientation == NORTH);
	return (dir);
}

t_obj	*create_player(t_vtr pos)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->lives = 3;
	player->pos = pos;
	player->dir = get_dir(pick_range(NORTH, SOUTH));
	player->plane.x = -player->dir.y * FOV;
	player->plane.y = player->dir.x * FOV;
	return ((t_obj *)player);
}
