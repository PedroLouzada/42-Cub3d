#include "cub3d.h"

t_obj	*create_enemy(void)
{
	t_enemy	*new_enemy;

	new_enemy = ft_calloc(1, sizeof(t_enemy));
	if (!new_enemy)
		return (NULL);
	return ((t_obj *)new_enemy);
}