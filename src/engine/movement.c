#include "cub3d.h"

int	key_press(int key)
{
	if (key == K_ESC)
		exit_game(NULL);
	if (key == K_E)
	{
		if (!game()->eng.current_map)
			return (0);
	}
	if (key == K_F || key == K_TAB || key == K_Q)
	{
		if (key == K_Q && !game()->eng.screen[2] && game()->map[0])
			return (0);
		game()->eng.key[key] = !game()->eng.key[key];
	}
	else
		game()->eng.key[key] = true;
	return (0);
}

int	key_unpress(int key)
{
	if (key == K_F || key == K_TAB)
		return (0);
	game()->eng.key[key] = false;
	return (0);
}

void	interact_door(t_player *p, t_map *map, t_ray *r)
{
	init_ray(r, (t_obj *)p, WIN_WIDTH / 2);
	while (1)
	{
		if (r->sDist.x < r->sDist.y)
		{
			r->sDist.x += r->dltDist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->sDist.y += r->dltDist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (!in_bounds(map->map, (int)r->map.y, (int)r->map.x))
			return ;
		if (r->side == 0)
			r->perp = r->sDist.x - r->dltDist.x;
		else
			r->perp = r->sDist.y - r->dltDist.y;
		if (r->perp > 1.5)
			return ;
		if (map->map[(int)r->map.y][(int)r->map.x] == '1')
			return ;
		if (map->map[(int)r->map.y][(int)r->map.x] == 'D')
		{
			map->map[(int)r->map.y][(int)r->map.x] = 'd';
			return ;
		}
		if (map->map[(int)r->map.y][(int)r->map.x] == 'd')
		{
			map->map[(int)r->map.y][(int)r->map.x] = 'D';
			return ;
		}
	}
}
