#include "cub3d.h"

void	draw_fov(t_ray *r, t_vtr pos, int type)
{
    int		i;
    t_vtr	s;
    t_vtr	e;

    s.x = pos.x * TILE_SZ;
    s.y = pos.y * TILE_SZ;
    i = -1;
    while (++i < WIN_WIDTH)
    {
		if (r[i].perp < 0 || r[i].perp > WIN_WIDTH)
            continue;
		if (r[i].perp > RANGE)
			r[i].perp = RANGE;
        e.x = (pos.x + r[i].dir.x * r[i].perp) * TILE_SZ;
        e.y = (pos.y + r[i].dir.y * r[i].perp) * TILE_SZ;
		if (type == E)
        	draw_line(s, e, PINK);
		if (type == P)
			draw_line(s, e, PURPLE);
    }
}

void 	darken_color(double distance, int radius, int *color, int type)
{
	int		rgb[3];
	double	intensity;
	double	brightness;

	if (*color < 0)
		return ;
	intensity = (distance - radius) / (radius * TILE_SZ);
	if (intensity > 1.0)
        intensity = 1.0;
	rgb[0] = (*color >> 16) & 0xFF;
	rgb[1] = (*color >> 8) & 0xFF;
	rgb[2] = *color & 0xFF;
    brightness = 1.0 - intensity;
	if (brightness < 0.125 && type != MINIMAP)
		brightness = 0.125;
    rgb[0] = (int)(rgb[0] * brightness);
    rgb[1] = (int)(rgb[1] * brightness);
    rgb[2] = (int)(rgb[2] * brightness);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

void	draw_flashlight(t_vtr size, int radius, int type)
{
	t_vtr	pos;
	t_vtr	draw;
    int		color;
	double	distance;

	pos.y = -1;
	while (++pos.y < size.y)
	{
		pos.x = -1;
		while (++pos.x < size.x)
		{
			draw.x = pos.x - (size.x / 2);
			draw.y = pos.y - (size.y / 2);
			distance = sqrt(draw.x * draw.x + draw.y * draw.y);
            if (distance < radius)
				continue ;
            color = ft_get_color(game()->mlx->img, (int)pos.x, (int)pos.y);
			darken_color(distance, radius, &color, type);
			if (color < 0)
				continue ;
            ft_pixel_put(game()->mlx, (int)pos.x, (int)pos.y, color);
		}
	}
}
