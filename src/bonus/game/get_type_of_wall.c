/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_of_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:40:17 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/31 20:02:04 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_dir	get_type_of_wall(t_param *prm, t_coord point)
{
	if (point.y == (int)point.y
		&& prm->map.map[(int)point.y][(int)point.x] == '1')
		return (SOUTH);
	if (point.y == (int)point.y && (int)point.y - 1 >= 0
		&& prm->map.map[(int)point.y - 1][(int)point.x] == '1')
		return (NORTH);
	if (point.x == (int)point.x
		&& prm->map.map[(int)point.y][(int)point.x] == '1')
		return (EAST);
	if (point.x == (int)point.x && (int)point.x - 1 >= 0
		&& prm->map.map[(int)point.y][(int)point.x - 1] == '1')
		return (WEST);
	return (get_type_of_wall_part_2(prm, point));
}

t_dir	get_type_of_wall_part_2(t_param *prm, t_coord point)
{
	if (has_hit_a_closed_door(prm, point))
		return (has_hit_a_closed_door(prm, point));
	if ((point.y == (int)point.y
			&& prm->map.map[(int)point.y][(int)point.x] == '3')
		|| (point.y == (int)point.y && (int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '3')
		|| (point.x == (int)point.x
			&& prm->map.map[(int)point.y][(int)point.x] == '3')
		|| (point.x == (int)point.x && (int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '3'))
		return (WALL_3);
	if ((point.y == (int)point.y
			&& prm->map.map[(int)point.y][(int)point.x] == '4')
		|| (point.y == (int)point.y && (int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '4')
		|| (point.x == (int)point.x
			&& prm->map.map[(int)point.y][(int)point.x] == '4')
		|| (point.x == (int)point.x && (int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '4'))
		return (WALL_4);
	return (get_type_of_wall_part_3(prm, point));
}

t_dir	get_type_of_wall_part_3(t_param *prm, t_coord point)
{
	if ((point.y == (int)point.y
			&& prm->map.map[(int)point.y][(int)point.x] == '5')
		|| (point.y == (int)point.y && (int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '5')
		|| (point.x == (int)point.x
			&& prm->map.map[(int)point.y][(int)point.x] == '5')
		|| (point.x == (int)point.x && (int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '5'))
		return (WALL_5);
	if ((point.y == (int)point.y
			&& prm->map.map[(int)point.y][(int)point.x] == '6')
		|| (point.y == (int)point.y && (int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '6')
		|| (point.x == (int)point.x
			&& prm->map.map[(int)point.y][(int)point.x] == '6')
		|| (point.x == (int)point.x && (int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '6'))
		return (WALL_6);
	return (get_type_of_wall_part_4(prm, point));
}

t_dir	get_type_of_wall_part_4(t_param *prm, t_coord point)
{
	if ((point.y == (int)point.y
			&& prm->map.map[(int)point.y][(int)point.x] == '7')
		|| (point.y == (int)point.y && (int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '7')
		|| (point.x == (int)point.x
			&& prm->map.map[(int)point.y][(int)point.x] == '7')
		|| (point.x == (int)point.x && (int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '7'))
		return (WALL_7);
	if ((point.y == (int)point.y
			&& prm->map.map[(int)point.y][(int)point.x] == '8')
		|| (point.y == (int)point.y && (int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '8')
		|| (point.x == (int)point.x
			&& prm->map.map[(int)point.y][(int)point.x] == '8')
		|| (point.x == (int)point.x && (int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '8'))
		return (WALL_8);
	return (get_type_of_wall_part_5(prm, point));
}

t_dir	get_type_of_wall_part_5(t_param *prm, t_coord point)
{
	if ((point.y == (int)point.y
			&& prm->map.map[(int)point.y][(int)point.x] == '9')
		|| (point.y == (int)point.y && (int)point.y - 1 >= 0
			&& prm->map.map[(int)point.y - 1][(int)point.x] == '9')
		|| (point.x == (int)point.x
			&& prm->map.map[(int)point.y][(int)point.x] == '9')
		|| (point.x == (int)point.x && (int)point.x - 1 >= 0
			&& prm->map.map[(int)point.y][(int)point.x - 1] == '9'))
		return (WALL_9);
	return (0);
}
