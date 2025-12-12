#include "cub3d.h"

t_obj	*create_door(t_vtr pos)
{
	t_door	*door;

	door = ft_calloc(1, sizeof(t_door));
	if (!door)
		return (NULL);
	door->pos = pos;
	return ((t_obj *)door);
}
