#include "so_long.h"

void free_map(char **map) {
        int i;

        i = 0;
        while (map[i])
                free(map[i++]);
        /*free(map);*/
        printf("The matrix must be free later\n");
}

void free_dynamic_charachter(t_game *game, t_walker *c)
{

        mlx_destroy_image(game->mlx, c->views[LEFT_1]);
        mlx_destroy_image(game->mlx, c->views[LEFT_2]);
        mlx_destroy_image(game->mlx, c->views[LEFT_3]);
        mlx_destroy_image(game->mlx, c->views[RIGHT_1]);
        mlx_destroy_image(game->mlx, c->views[RIGHT_2]);
        mlx_destroy_image(game->mlx, c->views[RIGHT_3]);
        mlx_destroy_image(game->mlx, c->views[TOP_1]);
        mlx_destroy_image(game->mlx, c->views[TOP_2]);
        mlx_destroy_image(game->mlx, c->views[TOP_3]);
        mlx_destroy_image(game->mlx, c->views[BOTTOM_1]);
        mlx_destroy_image(game->mlx, c->views[BOTTOM_2]);
        mlx_destroy_image(game->mlx, c->views[BOTTOM_3]);
        mlx_destroy_image(game->mlx, c->views[STAND_1]);
        mlx_destroy_image(game->mlx, c->views[STAND_2]);
        mlx_destroy_image(game->mlx, c->views[STAND_3]);
        free(c->pos);
        free(c->views);
        free(c);
}

void free_game_assets(t_game *game)
{
        mlx_destroy_image(game->mlx, game->assets->background);
        mlx_destroy_image(game->mlx, game->assets->wall);
        mlx_destroy_image(game->mlx, game->assets->empty);
        mlx_destroy_image(game->mlx, game->assets->peel);
        mlx_destroy_image(game->mlx, game->assets->header);
        mlx_destroy_image(game->mlx, game->assets->header_counter);
        mlx_destroy_image(game->mlx, game->assets->numbers[0]);
        mlx_destroy_image(game->mlx, game->assets->numbers[1]);
        mlx_destroy_image(game->mlx, game->assets->numbers[2]);
        mlx_destroy_image(game->mlx, game->assets->numbers[3]);
        mlx_destroy_image(game->mlx, game->assets->numbers[4]);
        mlx_destroy_image(game->mlx, game->assets->numbers[5]);
        mlx_destroy_image(game->mlx, game->assets->numbers[6]);
        mlx_destroy_image(game->mlx, game->assets->numbers[7]);
        mlx_destroy_image(game->mlx, game->assets->numbers[8]);
        mlx_destroy_image(game->mlx, game->assets->numbers[9]);
        free(game->assets->numbers);
        free_dynamic_charachter(game, game->assets->player);
        free(game->assets);
}


void clear_game(t_game *game)
{
        free_game_assets(game);
        free_map(game->map);
        free(game->keycode);
        mlx_destroy_window(game->mlx, game->window);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        free(game);
}
