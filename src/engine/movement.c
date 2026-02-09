#include "cub3d.h"

int	key_press(int key)
{
	if (key == K_ESC)
		exit_game(NULL);
    game()->eng->key[key] = true;
	return (0);
}

int key_unpress(int key)
{
    game()->eng->key[key] = false;
    return (0);
}
