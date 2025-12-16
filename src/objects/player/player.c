#include "cub3d.h"

t_obj	*create_player(void)
{
	t_player	*new_player;

	new_player = ft_calloc(1, sizeof(t_player));
	if (!new_player)
		return (NULL);
	return ((t_obj *)new_player);
}