#include "cub3d.h"

void	draw_fov(t_ray *r, t_obj *obj, int type)
{
    int		i;
    t_vtr	s;
    t_vtr	e;

    s.x = obj->pos.x * TILE_SZ;
    s.y = obj->pos.y * TILE_SZ;
    i = -1;
    while (++i < WIN_WIDTH)
    {
		if (r[i].perp < 0 || r[i].perp > WIN_WIDTH)
            continue;
        e.x = (obj->pos.x + r[i].dir.x * r[i].perp) * TILE_SZ;
        e.y = (obj->pos.y + r[i].dir.y * r[i].perp) * TILE_SZ;
		if (type == E)
        	draw_line(s, e, PINK);
		if (type == P)
			draw_line(s, e, PURPLE);
    }
}
