#include "cub3d.h"

void	idle_walk(t_enemy *enemy, t_map *map)
{
	t_vtr	new_pos;

	if (rand() % 100 < 5)
		enemy->angle += (rand() % 20 - 10) * 0.05;
	new_pos.x = enemy->pos.x + cos(enemy->angle) * 0.02;
	new_pos.y = enemy->pos.y + sin(enemy->angle) * 0.02;

	if (map->map[(int)new_pos.y][(int)new_pos.x] == '0')
	{
		enemy->pos.x = new_pos.x;
		enemy->pos.y = new_pos.y;
	}
	else
		enemy->angle += M_PI / 2;
}

void	e_update(t_obj *this, t_map *map)
{
	t_enemy					*enemy;
	static unsigned long	time;

	enemy = (t_enemy *)this;
	if (!time)
		time = get_time() + 10000;
	idle_walk(enemy, map);
	if (time <= get_time())
	{
		enemy->pos = spawn(game()->map[1], '0');
		time = get_time() + 10000;
	}
}

t_obj	*create_enemy(t_vtr pos)
{
	t_enemy *enemy;

	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	enemy->pos = pos;
	enemy->update = e_update;
	enemy->angle = 1;
	return ((t_obj *)enemy);
}