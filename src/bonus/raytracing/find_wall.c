/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:28:40 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/29 18:59:59 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_coord	find_wall_h(t_param *prm, double ray_ang, t_coord first_h)
{
	t_coord	delt_h;

	delt_h = first_h;
	while (ray_ang == PI / 2 && !has_hit_a_wall_or_door(prm, delt_h))
	{
		delt_h.x = delt_h.x;
		delt_h.y = (int)delt_h.y - 1;
	}
	while (ray_ang == 3 * PI / 2 && !has_hit_a_wall_or_door(prm, delt_h))
	{
		delt_h.x = delt_h.x;
		delt_h.y = (int)delt_h.y + 1;
	}
	find_wall_h_part_2(prm, ray_ang, &delt_h);
	return (delt_h);
}

void	find_wall_h_part_2(t_param *prm, double ray_ang, t_coord *delt_h)
{
	while (ray_ang > 0 && ray_ang < PI && ray_ang != PI / 2
		&& !has_hit_a_wall_or_door(prm, *delt_h))
	{
		delt_h->y = delt_h->y - 1;
		delt_h->x = delt_h->x + (1 / tan(ray_ang));
	}
	while (ray_ang > PI && ray_ang < 2 * PI && ray_ang != 3 * PI / 2
		&& !has_hit_a_wall_or_door(prm, *delt_h))
	{
		delt_h->y = delt_h->y + 1;
		delt_h->x = delt_h->x - (1 / tan(ray_ang));
	}
}

t_coord	find_wall_v(t_param *prm, double ray_ang, t_coord first_v)
{
	t_coord	delt_v;

	delt_v = first_v;
	while (ray_ang == 0 && !has_hit_a_wall_or_door(prm, delt_v))
	{
		delt_v.x = (int)delt_v.x + 1;
		delt_v.y = delt_v.y;
	}
	while (ray_ang == PI && !has_hit_a_wall_or_door(prm, delt_v))
	{
		delt_v.x = (int)delt_v.x - 1;
		delt_v.y = delt_v.y;
	}
	while (ray_ang != 0 && ray_ang < PI / 2
		&& !has_hit_a_wall_or_door(prm, delt_v))
	{
		delt_v.x = (int)delt_v.x + 1;
		delt_v.y = delt_v.y - tan(ray_ang);
	}
	find_wall_v_part_2(prm, ray_ang, &delt_v);
	return (delt_v);
}

void	find_wall_v_part_2(t_param *prm, double ray_ang, t_coord *delt_v)
{
	while (ray_ang != 2 * PI && ray_ang > 3 * PI / 2
		&& !has_hit_a_wall_or_door(prm, *delt_v))
	{
		delt_v->x = (int)delt_v->x + 1;
		delt_v->y = delt_v->y + tan(2 * PI - ray_ang);
	}
	while (ray_ang > PI / 2 && ray_ang < PI
		&& !has_hit_a_wall_or_door(prm, *delt_v))
	{
		delt_v->x = (int)delt_v->x - 1;
		delt_v->y = delt_v->y - tan(PI - ray_ang);
	}
	while (ray_ang > PI && ray_ang < 3 * PI / 2
		&& !has_hit_a_wall_or_door(prm, *delt_v))
	{
		delt_v->x = (int)delt_v->x - 1;
		delt_v->y = delt_v->y + tan(ray_ang - PI);
	}
}

t_coord	find_wall(t_param *prm, double ray_ang)
{
	t_coord	first_h;
	t_coord	delt_h;
	t_coord	first_v;
	t_coord	delt_v;

	first_h = find_first_h(prm, ray_ang);
	delt_h = find_wall_h(prm, ray_ang, first_h);
	first_v = find_first_v(prm, ray_ang);
	delt_v = find_wall_v(prm, ray_ang, first_v);
	if (!is_valid_coord(prm, delt_v) && is_valid_coord(prm, delt_h))
		return (delt_h);
	if (!is_valid_coord(prm, delt_h) && is_valid_coord(prm, delt_v))
		return (delt_v);
	if (get_distance(prm->pos_player, delt_v)
		< get_distance(prm->pos_player, delt_h))
		return (delt_v);
	return (delt_h);
}
