/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_to_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:12:52 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/07 15:28:54 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	pos_impact(t_param *prm, t_coord point)
{
	if (point.x < 0 || point.y < 0 || point.x >= prm->map.map_width
		|| point.y >= prm->map.map_height)
		return (-1);
	if (point.y == (int)point.y)
	{
		if (point.y - 1 >= 0 && ft_strchr("123456789D",
				prm->map.map[(int)point.y - 1][(int)point.x]))
			return ((point.x - (double)((int)point.x)));
		if (ft_strchr("123456789D", prm->map.map[(int)point.y][(int)point.x]))
			return (1 - (point.x - (double)((int)point.x)));
	}
	if (point.x == (int)point.x)
	{
		if (point.x - 1 >= 0 && ft_strchr("123456789D",
				prm->map.map[(int)point.y][(int)point.x - 1]))
			return (1 - (point.y - (double)((int)point.y)));
		if (ft_strchr("123456789D", prm->map.map[(int)point.y][(int)point.x]))
			return (point.y - (double)((int)point.y));
	}
	return (0);
}

/* t_img	*get_correct_xpm_part2(t_param *prm, t_dir dir)
{
	if (dir == WALL_5)
		return (&(prm->map.wall5_texture));
	if (dir == WALL_6)
		return (&(prm->map.wall6_texture));
	if (dir == WALL_7)
		return (&(prm->map.wall7_texture));
	if (dir == WALL_8)
		return (&(prm->map.wall8_texture));
	if (dir == WALL_9)
		return (&(prm->map.wall9_texture));
	return (&(prm->map.door_texture));
}

static t_img	*get_correct_xpm(t_param *prm, t_dir dir)
{
	if (dir == SOUTH)
		return (&(prm->map.south_texture));
	if (dir == NORTH)
		return (&(prm->map.north_texture));
	if (dir == EAST)
		return (&(prm->map.east_texture));
	if (dir == WEST)
		return (&(prm->map.west_texture));
	if (dir == WALL_2)
		return (&(prm->map.wall2_texture));
	if (dir == WALL_3)
		return (&(prm->map.wall3_texture));
	if (dir == WALL_4)
		return (&(prm->map.wall4_texture));
	return (get_correct_xpm_part2(prm, dir));
} */

void	init_tab_xpm(t_param *prm)
{
	prm->tab_xpm[SOUTH] = &(prm->map.south_texture);
	prm->tab_xpm[NORTH] = &(prm->map.north_texture);
	prm->tab_xpm[EAST] = &(prm->map.east_texture);
	prm->tab_xpm[WEST] = &(prm->map.west_texture);
	prm->tab_xpm[WALL_2] = &(prm->map.wall2_texture);
	prm->tab_xpm[WALL_3] = &(prm->map.wall3_texture);
	prm->tab_xpm[WALL_4] = &(prm->map.wall4_texture);
	prm->tab_xpm[WALL_5] = &(prm->map.wall5_texture);
	prm->tab_xpm[WALL_6] = &(prm->map.wall6_texture);
	prm->tab_xpm[WALL_7] = &(prm->map.wall7_texture);
	prm->tab_xpm[WALL_8] = &(prm->map.wall8_texture);
	prm->tab_xpm[WALL_9] = &(prm->map.wall9_texture);
	prm->tab_xpm[SOUTH_DOOR] = &(prm->map.door_texture);
	prm->tab_xpm[NORTH_DOOR] = &(prm->map.door_texture);
	prm->tab_xpm[WEST_DOOR] = &(prm->map.door_texture);
	prm->tab_xpm[EAST_DOOR] = &(prm->map.door_texture);
}

int	get_texture_px_color(t_param *prm, t_coord wall, double pos_y)
{
	int		px_x;
	int		px_y;
	t_dir	dir;

	dir = get_type_of_wall(prm, wall);
	px_x = (int)(pos_impact(prm, wall) * (double)prm->tab_xpm[dir]->width);
	px_y = (int)(pos_y * (double)prm->tab_xpm[dir]->height);
	if (px_x < 0 || px_x > prm->tab_xpm[dir]->width || px_y < 0
		|| px_y > prm->tab_xpm[dir]->height)
		return (-1);
	return (*(int *)(prm->tab_xpm[dir]->addr
		+ (px_x * (prm->tab_xpm[dir]->bits_per_pixel / 8)
			+ px_y * prm->tab_xpm[dir]->line_length)));
}

int	get_color_px(t_param *prm, t_px_col col, int y, t_coord wall)
{
	int		y_bis;
	double	pos_v_in_wall;

	y_bis = y + col.ofset;
	if (y_bis < col.px_cell)
		return (-1);
	if (y_bis >= col.px_cell + col.px_wall)
		return (-1);
	pos_v_in_wall = (double)(y_bis - col.px_cell) / (double)col.px_wall;
	return (darken_color(get_texture_px_color(prm, wall, pos_v_in_wall),
			wall, prm->pos_player));
}
