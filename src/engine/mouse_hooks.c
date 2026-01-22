#include "cub3d.h"

int	mouse_press(int button, int x, int y, void *arg)
{
	if (button == 1)
	{
		if (game()->eng->title[0])
		{
			if ((x >= 240 && x <= 640) && (y >= 320 && y <= 420))
				exit_game(NULL);
			else if ((x >= 240 && x <= 640) && (y >= 560 && y <= 660))
            {
                game()->eng->title[0] = false;
                game()->eng->title[1] = true;
            }
		}
		// else if (game()->eng->title[2])
	}
	(void)arg;
	return (0);
}

int	mouse_move(int x, int y, void *arg)
{
	if (!game()->eng->title[0])
		return (1);
	if ((x >= 240 && x <= 640) && (y >= 320 && y <= 420))
		game()->eng->in_button[0] = true;
	else if ((x >= 240 && x <= 640) && (y >= 440 && y <= 540))
		game()->eng->in_button[1] = true;
	else if ((x >= 240 && x <= 640) && (y >= 560 && y <= 660))
		game()->eng->in_button[2] = true;
	else
	{
		game()->eng->in_button[0] = false;
		game()->eng->in_button[1] = false;
		game()->eng->in_button[2] = false;
	}
	(void)arg;
	return (0);
}
