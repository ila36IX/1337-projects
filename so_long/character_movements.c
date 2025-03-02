#include "so_long.h"

void walk(t_game *game, t_walker *obj, int x, int y)
{
        if (obj->off_x || obj->off_y)
                return ;
        if (!can_move(game, obj, x, y))
                return ;
        obj->off_x = x;
        obj->off_y = y;
        obj->_off_x = 0;
        obj->_off_y = 0;
}

void    move_to_next_cell(t_game *game, t_walker *p)
{
        if (p->off_x > 0)
                move_right(p);
        else if (p->off_x < 0)
                move_left(p);
        else if (p->off_y > 0)
                move_bottom(p);
        else if (p->off_y < 0)
                move_top(p);
}

void move_left(t_walker *asset)
{
        if (asset->off_y || !asset->off_x)
                return ;
        asset->_off_y = 0;
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
        if (asset->off_y || !asset->off_x)
                return ;
        asset->_off_y = 0;
        asset->off_x += FRAME_RATE;
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
                asset->_off_y = 0;
                asset->pos->y--;
        }
}
