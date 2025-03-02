#include "so_long.h"

void update_face(int *index, int start)
{
        if (*index <= start + 1 && *index >= start)
                ++*index;
        else
                *index = start;
}

void next_img(t_game *game, t_walker *obj)
{
        if (!obj->off_x && !obj->off_y)
        {
                for (int i = 0; i < 4; i++)
                        if (game->keycode[i])
                                return ;
                update_face(&obj->curr, STAND_1);
        }
        else if (obj->off_x > 0)
                update_face(&obj->curr, RIGHT_1);
        else if (obj->off_x < 0)
                update_face(&obj->curr, LEFT_1);
        else if (obj->off_y > 0)
                update_face(&obj->curr, BOTTOM_1);
        else if (obj->off_y < 0)
                update_face(&obj->curr, TOP_1);
}

void    set_next_frame_content(t_game *game)
{
        int j; 
        j  = 0;
        next_img(game, game->assets->player);
        while (game->assets->enemies[j])
        {
                next_img(game, game->assets->enemies[j]);
                j++;
        }
}
