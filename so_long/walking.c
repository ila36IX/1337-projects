#include "so_long.h"

void *init_img(t_game *game, char *path);

void draw_walker(t_game *game, t_walker *charachter)
{
        int x;
        int y;
        t_data *view;
        t_data *erase;

        view = charachter->views[charachter->curr];
        erase = charachter->views[NONE];
        mlx_put_image_to_window(game->mlx, game->window, erase,
                                charachter->pos->x * IMG_SIZE + charachter->_off_x,
                                charachter->pos->y * IMG_SIZE + charachter->_off_y);
        mlx_put_image_to_window(game->mlx, game->window, view,
                                charachter->pos->x * IMG_SIZE + charachter->off_x,
                                charachter->pos->y* IMG_SIZE + charachter->off_y);
        charachter->_off_x = charachter->off_x;
        charachter->_off_y = charachter->off_y;
}

void move_left(t_walker *asset)
{
        if (asset->off_y || !asset->off_x)
                return ;
        asset->_off_y = 0;
        /*asset->_off_x = asset->off_x;*/
        asset->off_x -= FRAME_RATE;
        if (asset->off_x * -1 > IMG_SIZE)
        {
                asset->off_x = 0;
                asset->_off_x = 0;
                asset->pos->x--;
        }
}

void move_right(t_walker *asset)
{
        printf("RIGHT==>\n");
        if (asset->off_y || !asset->off_x)
                return ;
        asset->_off_y = 0;
        /* asset->_off_x = asset->off_x; */
        printf("RIGHT==>--- %d\n", asset->off_x);
        asset->off_x += FRAME_RATE;
        printf("RIGHT==>+++ %d\n", asset->off_x);
        if (asset->off_x > IMG_SIZE)
        {
                asset->off_x = 0;
                asset->_off_x = 0;
                asset->pos->x++;
        }
}

void move_bottom(t_walker *asset)
{
        if (!asset->off_y || asset->off_x)
                return ;
        asset->_off_x = 0;
        asset->off_y += FRAME_RATE;
        if (asset->off_y > IMG_SIZE)
        {
                asset->off_y = 0;
                asset->_off_y = 0;
                asset->pos->y++;
        }
}

void move_top(t_walker *asset)
{
        if (!asset->off_y || asset->off_x)
                return ;
        asset->_off_x = 0;
        asset->off_y -= FRAME_RATE;
        if (asset->off_y * -1 > IMG_SIZE)
        {
                asset->off_y = 0;
                asset->off_y = 0;
                asset->pos->y--;
        }
}
