#include "cub3d.h"

t_player	*create_player(void)
{
	t_player	*new_player;

	new_player = ft_calloc(1, sizeof(t_player));
	if (!new_player)
		return (NULL);
	return (new_player);
}