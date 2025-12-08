#include "cub3d.h"

t_enemy	*create_enemy(void)
{
	t_enemy	*new_enemy;

	new_enemy = ft_calloc(1, sizeof(t_enemy));
	if (!new_enemy)
		return (NULL);
	return (new_enemy);
}