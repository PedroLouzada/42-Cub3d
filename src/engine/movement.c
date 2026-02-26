#include "cub3d.h"

int	key_press(int key)
{
	if (key == K_ESC)
		exit_game(NULL);
	if (key == K_F && game()->eng->key[key] == true)
	{
		game()->eng->key[key] = false;
		return (0);
	}
	game()->eng->key[key] = true;
	return (0);
}

int key_unpress(int key)
{
	if (key == K_F)
		return (0);
    game()->eng->key[key] = false;
    return (0);
}
