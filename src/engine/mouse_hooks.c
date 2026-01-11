#include "cub3d.h"

int mouse_press(int button, int x, int y, void *arg)
{
    if (button == 1)
    {
        if (game()->eng->title)
        {
            if ((x >= 240 && x <= 640) && (y >= 320 && y <= 420))
                exit_game();
        }
    }
    (void)arg;
    return (0);
}
