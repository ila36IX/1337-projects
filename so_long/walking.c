#include "so_long.h"

void *init_img(t_game *game, char *path);

void draw_walker(t_game *game, t_walker *asset)
{
        int x;
        int y;
        t_data *view;
        t_data *erase;

        view = asset->views[asset->curr];
        erase = asset->views[NONE];
        mlx_put_image_to_window(game->mlx, game->window, erase,
                                asset->pos->x * IMG_SIZE + asset->_off_x,
                                asset->pos->y * IMG_SIZE + asset->_off_y);
        mlx_put_image_to_window(game->mlx, game->window, view,
                                asset->pos->x * IMG_SIZE + asset->off_x,
                                asset->pos->y* IMG_SIZE + asset->off_y);
        asset->_off_x = asset->off_x;
        asset->_off_y = asset->off_y;
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
                asset->pos->x--;
        }
}

void move_right(t_walker *asset)
{
        if (asset->off_y || !asset->off_x)
                return ;
        asset->_off_y = 0;
        /* asset->_off_x = asset->off_x; */
        asset->off_x += FRAME_RATE;
        if (asset->off_x * 1 > IMG_SIZE)
        {
                asset->off_x = 0;
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
                asset->pos->y--;
        }
}
