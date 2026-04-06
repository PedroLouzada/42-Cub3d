#include "cub3d.h"

void	p_update(t_obj *obj, t_map *map)
{
	t_player	*p;

	p = (t_player *)obj;
	if (game()->eng.key[K_LEFT] || game()->eng.key[K_RIGHT])
		p_rotate(&game()->eng, p);
	if (game()->eng.key[K_W] || game()->eng.key[K_S] || game()->eng.key[K_A]
		|| game()->eng.key[K_D])
		p_walk(&game()->eng, p, map);
	if (game()->eng.key[K_F] == true && p->battery > 0)
		p->battery -= 5 * game()->eng.dt;
	else if (game()->eng.key[K_F] == false && p->battery < 100)
		p->battery += 4 * game()->eng.dt;
	else if (p->battery <= 0 && game()->eng.key[K_F] == true)
		game()->eng.key[K_F] = false;
	if (game()->eng.key[SHIFT] && p->stamina >= 0)
		p->stamina -= 30 * game()->eng.dt;
	else if (p->stamina < 100)
		p->stamina += 20 * game()->eng.dt;
	if (game()->eng.key[K_E] && !game()->eng.door)
	{
		interact_door(p, map, p->ray);
		game()->eng.door = true;
	}
	if (!game()->eng.key[K_E])
		game()->eng.door = false;
}

double	get_angle(char dir)
{
	if (dir == 'E')
		return (0);
	if (dir == 'N')
		return (M_PI_2);
	if (dir == 'W')
		return (M_PI);
	if (dir == 'S')
		return (3 * M_PI_2);
	return (-1);
}

t_obj	*create_player(t_vtr pos)
{
	t_player	*p;
	static int	i;

	p = ft_calloc(1, sizeof(t_player));
	if (!p)
		return (NULL);
	p->ray = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray));
	if (!p->ray)
	{
		free(p);
		return (NULL);
	}
	p->lives = 3;
	p->pos = pos;
	p->battery = 100;
	p->level = i++;
	p->stamina = 100.00;
	p->update = p_update;
	if (p->level)
		p->angle = pick_rand(pick_rand(M_PI_2, 0), pick_rand(M_PI, 3 * M_PI_2));
	else
		p->angle = get_angle(game()->map[0]->direction);
	set_p_orientation(p);
	return ((t_obj *)p);
}
