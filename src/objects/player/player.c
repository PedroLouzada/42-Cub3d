#include "cub3d.h"

int get_fov(char direction)
{
	if (direction == "N")
		return (0);
	else if (direction == "E")
		return (90);
	else if (direction == "S")
		return (180);
	else if (direction == "W")
		return (270);
	else
		return (-1);
}

t_obj *create_player(int level)
{
	t_player *new_player;

	new_player = ft_calloc(1, sizeof(t_player));
	if (!new_player)
		return (NULL);
	new_player->fov = get_fov(game()->map[level]->direction);
	return ((t_obj *)new_player);
}

static void movement()
{
}