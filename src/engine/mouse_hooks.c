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

int mouse_move(int x, int y, void *arg)
{
    t_imgs *curr;

    if (!game()->eng->title)
        return (0);
    if ((x >= 240 && x <= 640) && (y >= 320 && y <= 420))
    {
        curr = game()->mlx->img;
        while (curr->index < 5)
            curr = curr->next;
        draw_img(curr, 240, 320);
    }
    (void)arg;
    return (0);
}