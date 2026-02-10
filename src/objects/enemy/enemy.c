#include "cub3d.h"

t_obj	*create_enemy(t_vtr pos)
{
	t_enemy	*enemy;

	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	enemy->pos = pos;
	return ((t_obj *)enemy);
}