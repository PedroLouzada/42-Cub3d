/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:53 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/08 11:30:10 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	menu_button_press(int x, int y)
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

int	mouse_press(int button, int x, int y)
{
	if (button == 1)
	{
		if (game()->eng.screen[0])
			menu_button_press(x, y);
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
	int			mx;
	int			my;
	int			dx;
	t_player	*p;

	mx = WIN_WIDTH / 2;
	my = WIN_HEIGHT / 2;
	dx = x - mx;
	p = (t_player *)game()->map[game()->eng.current_map]->objs[P];
	game()->map[game()->eng.current_map]->objs[P]->angle += dx * 0.0009;
	set_p_orientation(p);
	mlx_mouse_move(game()->mlx->mlx, game()->mlx->win, mx, my);
}

int	mouse_move(const int x, const int y)
{
	if (game()->eng.screen[0] || game()->eng.screen[1])
		button_highlight(x, y);
	else if (game()->eng.key[K_TAB])
		mouse_rotate(x);
	return (0);
}
