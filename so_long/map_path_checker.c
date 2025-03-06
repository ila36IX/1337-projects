/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:46:02 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/05 01:56:29 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void print_ids(int **combs, int width, int  height )
{
        int x;
        int y;

        y = 0;
        while (y < height)
        {
                x = 0;
                while (x < width)
                {

                        if (combs[y][x]  > 0)
                                ft_printf("\e[%dm%2d\e[0m ", combs[y][x] + 26, combs[y][x]);
                        else
                                ft_printf("%2d ", combs[y][x]);
                        x++;
                }
                ft_printf("\n");
                y++;
        }

}

void last_check(char **map, int **combs, int width, int height)
{
        int x;
        int y;
        int same_id;

        y = 0;
        while (y < height)
        {
                x = 0;
                while (x < width)
                {
                        if (map[y][x] == 'P')
                                same_id = combs[y][x];
                        x++;
                }
                y++;
        }
        y = 0;
        while (y < height)
        {
                x = 0;
                while (x < width)
                {

                        if (map[y][x] == 'C' || map[y][x] == 'E')
                        {
                                if (combs[y][x] != same_id)
                                {
                                        printf("Not a valid map\n");
                                        exit(1);
                                }

                        }
                        x++;
                }
                y++;
        }
        printf("The max is valid :)");
        
}

void combs_replace(int **combs, int old, int new, int width, int height)
{
        int x;
        int y;


        y = 0;
        while (y < height)
        {
                x = 0;
                while (x < width)
                {
                        if (combs[y][x] == old)
                                combs[y][x] = new;
                        x++;
                }
                y++;
        }
        /*print_ids(combs, width, height);*/
        /*exit(EXIT_SUCCESS);*/


}

void    helper_path_exits(char **map, int **combs, int width, int height)
{
        int x;
        int y;
        int id;

        
        id = 1;
        y = 0;
        printf("-- %d, | %d\n", width, height);
        while (y < height)
        {
                x = 0;
                /*printf("Width %d, %d\n", x, width);*/
                while (x < width)
                {
                        if  (map[y][x] == '1')
                                combs[y][x] = -1;
                        else if (y > 1 && combs[y - 1][x] > 0 && x > 1 && combs[y][x - 1] > 0 && combs[y - 1][x] != combs[y][x - 1])
                        {
                                combs[y][x] = combs[y - 1][x];
                                combs_replace(combs, combs[y][x - 1], combs[y - 1][x], width, height);
                        }
                        else if (y > 1 && combs[y - 1][x] > 0)
                                        combs[y][x] = combs[y - 1][x];
                        else if (x > 1 && combs[y][x - 1] > 0)
                                        combs[y][x] = combs[y][x - 1];
                        else
                                        combs[y][x] = ++id;
                        x++;
                        /*print_ids(combs, width, height);*/
                        /*ft_printf("\n");*/
                }
                y++;
                /*printf("testing %d, %d\n", y, height);*/
        }
        print_ids(combs, width, height);
        last_check(map, combs, width, height);
}

void    path_exits(char **map)
{
        int x;
        int y;
        int **union_finder;

        x = ft_strlen(map[0]);
        y = 0;
        while (map[y])
                y++;
        int i;
        i = 0;
        union_finder = ft_calloc(y, sizeof(int *));
        i = 0;
        while (i < y)
                union_finder[i++] = ft_calloc(x, sizeof(int));
        helper_path_exits(map, union_finder, x, y);
        /*printf("worked :)");*/
        exit(EXIT_SUCCESS);
}

