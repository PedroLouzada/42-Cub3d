#include "cub3d.h"

int	key_press(int key)
{	if (key == K_ESC)
		exit_game(NULL);
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

int key_unpress(int key)
{
	if (key == K_F || key == K_TAB)
		return (0);
    game()->eng.key[key] = false;
    return (0);
}
