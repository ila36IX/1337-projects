/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_movements1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:39:37 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 02:55:14 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_left(t_walker *asset)
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

void	move_right(t_walker *asset)
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

void	move_bottom(t_walker *asset)
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

void	move_top(t_walker *asset)
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
