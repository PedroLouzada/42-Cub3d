#include "cub3d.h"

void	p_update(t_obj *obj, t_map *map)
{
	t_player	*p;

	p = (t_player *)obj;
	if (game()->eng->key[K_LEFT] || game()->eng->key[K_RIGHT])
		p_rotate(game()->eng, p);
	if (game()->eng->key[K_W] || game()->eng->key[K_S]
	|| game()->eng->key[K_A] || game()->eng->key[K_D])
		p_walk(game()->eng, p, map);
	// if (game()->eng->key[K_F] == true && p->battery > 0)
	// 	p->battery -= game()->eng->dt * 2;
	// if (game()->eng->key[K_F] == false && p->battery < 100)
	// 	p->battery += game()->eng->dt / 3;
	// if (game()->eng->key[K_F] == true && p->battery < 0.1)
	// 	game()->eng->key[K_F] = false;
}

t_obj	*create_player(t_vtr pos)
{
	t_player	*p;

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
	p->update = p_update;
	p->angle = pick_rand(pick_rand(M_PI_2, 0), pick_rand(M_PI, 3 * M_PI_2));
	set_p_orientation(p);
	return ((t_obj *)p);
}
