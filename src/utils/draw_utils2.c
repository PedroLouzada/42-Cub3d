#include "cub3d.h"

void	draw_fov(t_map *m, t_player *p)
{
    int		i;
    t_vtr	s;
    t_vtr	e;

    s.x = p->pos.x * TILE_SZ;
    s.y = p->pos.y * TILE_SZ;
    i = -1;
    while (++i < WIN_WIDTH)
    {
		if (m->rays[i].perp < 0 || m->rays[i].perp > WIN_WIDTH)
            continue;
        e.x = (p->pos.x + m->rays[i].dir.x * m->rays[i].perp) * TILE_SZ;
        e.y = (p->pos.y + m->rays[i].dir.y * m->rays[i].perp) * TILE_SZ;
        draw_line(s, e);
    }
}
