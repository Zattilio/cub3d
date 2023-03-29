/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:23:21 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/29 13:32:00 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_starting_pos(t_param *prm, int *x, int *y)
{
	*y = 0;
	while (prm->map.map[*y])
	{
		*x = 0;
		while (prm->map.map[*y][*x])
		{
			if (prm->map.map[*y][*x] == 'N'
				|| prm->map.map[*y][*x] == 'S'
				|| prm->map.map[*y][*x] == 'E'
				|| prm->map.map[*y][*x] == 'W')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

static void	init_east_west_player_pos(t_param *prm, int x, int y)
{
	if (prm->map.map[y][x] == 'E')
	{
		prm->view_dir.x = 1;
		prm->view_dir.y = 0;
		prm->screen_dir.x = 0;
		prm->screen_dir.y = 1;
		prm->view_ang = 0;
	}
	if (prm->map.map[y][x] == 'W')
	{
		prm->view_dir.x = -1;
		prm->view_dir.y = 0;
		prm->screen_dir.x = 0;
		prm->screen_dir.y = -1;
		prm->view_ang = PI;
	}
}

static void	init_north_south_player_pos(t_param *prm, int x, int y)
{
	if (prm->map.map[y][x] == 'N')
	{
		prm->view_dir.x = 0;
		prm->view_dir.y = -1;
		prm->screen_dir.x = 1;
		prm->screen_dir.y = 0;
		prm->view_ang = PI / 2;
	}
	if (prm->map.map[y][x] == 'S')
	{
		prm->view_dir.x = 0;
		prm->view_dir.y = 1;
		prm->screen_dir.x = -1;
		prm->screen_dir.y = 0;
		prm->view_ang = -1 * PI / 2;
	}
}

void	init_player_pos(t_param *prm)
{
	int	x;
	int	y;

	get_starting_pos(prm, &x, &y);
	prm->pos_player.x = (double)x + 0.5;
	prm->pos_player.y = (double)y + 0.5;
	init_east_west_player_pos(prm, x, y);
	init_north_south_player_pos(prm, x, y);
	prm->map.map[y][x] = '0';
}