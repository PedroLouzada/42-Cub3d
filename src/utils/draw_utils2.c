#include "cub3d.h"

void	draw_fov(t_map *map, t_ray *r, t_vtr pos)
{
	double	len;
    int		i[3];
    t_vtr	data[2];

	i[0] = (WIN_WIDTH / 4);
	i[1] = (WIN_WIDTH / 4) * 3;
    i[2] = i[0] - 1 ;
    while (++i[2] < i[1])
    {
		if (r[i[2]].perp < 0)
            continue;
		len = ft_min(r[i[2]].perp, RANGE);
		data[0] = pos;
        data[1].x = pos.x + (r[i[2]].dir.x * len) * TILE_SZ;
        data[1].y = pos.y + (r[i[2]].dir.y * len) * TILE_SZ;
		draw_line(data[0], data[1], FLOOR);
    }
}

int 	darken_color(double distance, double radius, int color, bool minimap)
{
	int		rgb[3];
	double	max_dist;
	double	intensity;
	double	brightness;

	if (color < 0)
		return (-1);
	if (color == CLEAR)
		return (color);
	max_dist = radius * TILE_SZ;
	intensity = distance / (max_dist * max_dist);
	if (intensity > 1.0)
        intensity = 1.0;
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
    brightness = 1.0 - intensity;
	if (brightness < 0.125)
		brightness = 0.125;
	if (minimap)
		brightness = 0.225;
	rgb[0] = (int)(rgb[0] * brightness);
    rgb[1] = (int)(rgb[1] * brightness);
    rgb[2] = (int)(rgb[2] * brightness);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	draw_flashlight(t_vtr size, int radius, bool minimap)
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
			distance = draw.x * draw.x + draw.y * draw.y;
            if (distance < radius * radius)
				continue ;
            color = ft_get_color(game()->mlx->img[BUFFER], (int)pos.x, (int)pos.y);
			color = darken_color(distance, radius, color, minimap);
			if (color < 0)
				continue ;
            ft_pixel_put(game()->mlx->img[BUFFER], (int)pos.x, (int)pos.y, color);
		}
	}
}

