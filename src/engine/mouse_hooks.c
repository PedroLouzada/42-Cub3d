#include "cub3d.h"

int	mouse_press(int button, int x, int y)
{
	if (button == 1)
	{
		if (game()->eng.screen[0])
		{
			if ((x >= 240 && x <= 640) && (y >= 320 && y <= 420))
			{
				game()->eng.screen[0] = false;
				game()->eng.screen[1] = false;
				game()->eng.current_map = 1;
			}
			else if ((x >= 240 && x <= 640) && (y >= 560 && y <= 660))
			{
				game()->eng.screen[0] = false;
				game()->eng.screen[1] = true;
			}
			else if ((x >= 240 && x <= 640) && (y >= 440 && y <= 540))
			{
				game()->eng.screen[0] = false;
				game()->eng.screen[1] = false;
				game()->eng.screen[2] = true;
			}
		}
		else if (game()->eng.screen[1])
		{
			if ((x >= 90 && x <= 390) && (y >= 850 && y <= 950))
			{
				game()->eng.screen[0] = true;
				game()->eng.screen[1] = false;
			}
		}
	}
	return (0);
}

static void	button_highlight(const int x, const int y)
{
	int	i;

	i = 0;
	if (game()->eng.screen[0])
	{
		while (i < 3)
			game()->eng.in_button[i++] = false;
		if ((x >= 240 && x <= 640) && (y >= 320 && y <= 420))
			game()->eng.in_button[0] = true;
		else if ((x >= 240 && x <= 640) && (y >= 440 && y <= 540))
			game()->eng.in_button[1] = true;
		else if ((x >= 240 && x <= 640) && (y >= 560 && y <= 660))
			game()->eng.in_button[2] = true;
	}
	else if (game()->eng.screen[1])
	{
		game()->eng.in_button[3] = false;
		if ((x >= 90 && x <= 390) && (y >= 850 && y <= 950))
			game()->eng.in_button[3] = true;
	}
}

static void	mouse_rotate(const int x)
{
	int	dx;

	dx = x - WIN_WIDTH / 2;
	game()->map[game()->eng.current_map]->objs[P]->angle += dx * 0.0009;
	set_p_orientation((t_player *)game()->map[game()->eng.current_map]->objs[P]);
	mlx_mouse_move(game()->mlx->mlx, game()->mlx->win, WIN_WIDTH / 2, WIN_HEIGHT
		/ 2);
}

int	mouse_move(const int x, const int y)
{
	if (game()->eng.screen[0] || game()->eng.screen[1])
		button_highlight(x, y);
	else if (game()->eng.key[K_TAB])
		mouse_rotate(x);
	return (0);
}
