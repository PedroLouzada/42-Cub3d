/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:52:42 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 16:50:37 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_game(void)
{
	t_enemy			*e;
	t_player		*p;
	static double	prev;
	static double	curr;

	curr = get_time();
	game()->eng.dt = curr - prev;
	if (game()->eng.dt > 0.1)
		game()->eng.dt = 0.1;
	prev = curr;
	e = (t_enemy *)game()->map[game()->eng.current_map]->objs[E];
	p = (t_player *)game()->map[game()->eng.current_map]->objs[P];
	if (game()->eng.current_map)
		e->update((t_obj *)e, game()->map[game()->eng.current_map]);
	p->update((t_obj *)p, game()->map[game()->eng.current_map]);
}

int	run(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	update_game();
	draw_screen(game()->mlx);
	mlx_mouse_get_pos(game()->mlx->mlx, game()->mlx->win, &x, &y);
	mouse_move(x, y);
	if (game()->eng.screen[2])
	{
		if (game()->eng.key[K_Q])
		{
			game()->eng.screen[0] = true;
			game()->eng.screen[2] = false;
		}
	}
	if (game()->eng.key[K_E])
		usleep(33);
	return (0);
}

void	declare_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 0, exit_game, 0);
	mlx_hook(mlx->win, 2, (1L << 0), key_press, game);
	mlx_hook(mlx->win, 3, (1L << 1), key_unpress, game);
	mlx_hook(mlx->win, 4, 1L << 2, mouse_press, NULL);
	mlx_loop_hook(mlx->mlx, run, game()->map);
}

void	mlx_alloc(char **av)
{
	game()->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!game()->mlx)
		parse_exit("Memory Allocation\n", NULL, -1, 0);
	game()->mlx->mlx = mlx_init();
	if (!game()->mlx->mlx)
		parse_exit("Memory Allocation\n", NULL, -1, 0);
	parsing(av);
	(game()->mlx)->win = mlx_new_window((game()->mlx)->mlx, WIN_WIDTH,
			WIN_HEIGHT, TITLE);
	if (!game()->mlx->win)
		parse_exit("Memory Allocation\n", NULL, -1, 1);
}

void	init_game(int ac, t_str *av)
{
	int	i;

	if (ac != 2)
		parse_exit("Expected <fileName> <map.cub>\n", NULL, -1, 0);
	mlx_alloc(av);
	alloc_assets();
	init_rand();
	i = 0;
	while (++i < 6)
		(game()->map)[i] = create_map(i, -1);
	declare_hooks(game()->mlx);
	game()->eng.pool = init_tpool(4);
	mlx_loop(game()->mlx->mlx);
}
