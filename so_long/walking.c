#include "so_long.h"

void *init_img(t_game *game, char *path);

void draw_offset_asset(t_game *game, t_moving_asset *asset, int pex_x, int pex_y)
{
        int x;
        int y;
        t_data *view;
        t_data *erase;

        view = asset->views[asset->curr];
        erase = asset->views[NONE];
        mlx_put_image_to_window(game->mlx, game->window, erase, pex_x * IMG_SIZE + asset->_off_x,  pex_y * IMG_SIZE + asset->_off_y);
        mlx_put_image_to_window(game->mlx, game->window, view, pex_x * IMG_SIZE + asset->off_x,  pex_y * IMG_SIZE + asset->off_y);
        asset->_off_x = asset->off_x;
        asset->_off_y = asset->off_y;
}




void move_left(t_pos *pos, t_moving_asset *asset)
{
        if (asset->off_y || !asset->off_x)
                return ;
        asset->_off_y = 0;
        /*asset->_off_x = asset->off_x;*/
        asset->off_x -= FRAME_RATE;
        if (asset->off_x * -1 > IMG_SIZE)
        {
                asset->off_x = 0;
                pos->x--;
        }
}

void move_right(t_pos *pos, t_moving_asset *asset)
{
        if (asset->off_y || !asset->off_x)
                return ;
        asset->_off_y = 0;
        /*asset->_off_x = asset->off_x;*/
        asset->off_x += FRAME_RATE;
        if (asset->off_x * 1 > IMG_SIZE)
        {
                asset->off_x = 0;
                pos->x++;
        }
}

void move_bottom(t_pos *pos, t_moving_asset *asset)
{
        if (!asset->off_y || asset->off_x)
                return ;
        asset->_off_x = 0;
        asset->off_y += FRAME_RATE;
        if (asset->off_y > IMG_SIZE)
        {
                asset->off_y = 0;
                pos->y++;
        }
}

void move_top(t_pos *pos, t_moving_asset *asset)
{
        if (!asset->off_y || asset->off_x)
                return ;
        asset->_off_x = 0;
        asset->off_y -= FRAME_RATE;
        if (asset->off_y * -1 > IMG_SIZE)
        {
                asset->off_y = 0;
                pos->y--;
        }
}
