/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:23:42 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/10 14:39:36 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	case_pos_buff_enemy(t_param *prm, double ang_move,
	t_coord pos, double buf)
{
	if (ang_move > 0 && ang_move < PI
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y) - 1][(int)(pos.x)])
			&& pos.y - (int)(pos.y) < buf)
		return (1);
	if (ang_move > PI && ang_move < 2 * PI
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y) + 1][(int)(pos.x)])
			&& (int)(pos.y) + 1 - pos.y < buf)
		return (2);
	return (3);
}

t_coord	pos_buff_enemy(t_param *prm, t_coord pos, double ang_move)
{
	t_coord	new_pos;

	new_pos = pos;
	if (case_pos_buff_enemy(prm, ang_move, pos, BUF) == 1)
		new_pos.y = (int)(pos.y) + BUF;
	if (case_pos_buff_enemy(prm, ang_move, pos, BUF) == 2)
		new_pos.y = (int)(pos.y) + 1 - BUF;
	if ((ang_move > (3 * PI) / 2 || ang_move < PI / 2)
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y)][(int)(pos.x) + 1])
			&& (int)(pos.x) + 1 - pos.x < BUF)
		new_pos.x = (int)(pos.x + 1) - BUF;
	if (ang_move > PI / 2 && ang_move < (3 * PI) / 2
		&& ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y)][(int)(pos.x) - 1])
			&& pos.x - (int)(pos.x) < BUF)
		new_pos.x = (int)pos.x + BUF;
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y)][(int)(pos.x) - 1])
	&& ft_strchr("123456789BD", prm->map.map[(int)(pos.y)][(int)(pos.x) + 1]))
		new_pos.x = (double)((int)(pos.x)) + 0.5;
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y - 1)][(int)(pos.x)])
	&& ft_strchr("123456789BD", prm->map.map[(int)(pos.y + 1)][(int)(pos.x)]))
		new_pos.y = (double)((int)(pos.y)) + 0.5;
	return (new_pos);
}

/*
t_coord	pos_buff_enemy(t_param *prm, t_coord pos)
{
	t_coord	new_pos;

	new_pos = pos;
	//cas couloir
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y)][(int)(pos.x) - 1])
	&& ft_strchr("123456789BD", prm->map.map[(int)(pos.y)][(int)(pos.x) + 1]))
		new_pos.x = (double)((int)(pos.x)) + 0.5;
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y - 1)][(int)(pos.x)])
	&& ft_strchr("123456789BD", prm->map.map[(int)(pos.y + 1)][(int)(pos.x)]))
		new_pos.x = (double)((int)(pos.y)) + 0.5;
	
	ft_strchr("123456789BD", prm->map.map[(int)(pos.y)][(int)(pos.x) + 1]
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y)][(int)(pos.x) + 1])
		&& (double)((int)(pos.x) + 1) - pos.x < BUF_ENEMY)
		new_pos.x = (double)((int)(pos.x) + 1) - BUF_ENEMY;
	else if (ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y)][(int)(pos.x) - 1])
	&& pos.x - (double)((int)pos.x) < BUF_ENEMY)
		new_pos.x = (double)((int)(pos.x)) + BUF_ENEMY;
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y) - 1][(int)(pos.x)])
		&& pos.y - (double)((int)pos.y) < BUF_ENEMY)
		new_pos.y = (double)((int)pos.y) + BUF_ENEMY;
	else if (ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y) + 1][(int)(pos.x)])
		&& (double)((int)(pos.y) + 1) - pos.y < BUF_ENEMY)
		new_pos.y = (double)((int)(pos.y) + 1) - BUF_ENEMY;
	return (new_pos);
}*/
/*
t_coord	pos_buff_enemy(t_param *prm, t_coord pos)
{
	t_coord	new_pos;

	new_pos = pos;
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y)][(int)(pos.x) + 1])
		&& (double)((int)(pos.x) + 1) - pos.x < BUF_ENEMY)
		new_pos.x = (double)((int)(pos.x) + 1) - BUF_ENEMY;
	else if (ft_strchr("123456789BD",
			prm->map.map[(int)(pos.y)][(int)(pos.x) - 1])
	&& pos.x - (double)((int)pos.x) < BUF_ENEMY)
		new_pos.x = (double)((int)(pos.x)) + BUF_ENEMY;
	if (ft_strchr("123456789BD", prm->map.map[(int)(pos.y) - 1][(int)(pos.x)])
		&& pos.y - (double)((int)pos.y) < BUF_ENEMY)
		new_pos.y = (double)((int)pos.y) + BUF_ENEMY;
	else if (ft_strchr("123pos_buff_enemy456789BD",
			prm->map.map[(int)(pos.y) + 1][(int)(pos.x)])
		&& (double)((int)(pos.y) + 1) - pos.y < BUF_ENEMY)
		new_pos.y = (double)((int)(pos.y) + 1) - BUF_ENEMY;
	return (new_pos);
}
*/
static t_coord	get_wanted_move_dir_enemy_p2(double ang, t_coord *coord)
{
	if (ang > PI / 2 && ang < PI)
	{
		coord->x = -cos(PI - ang);
		coord->y = -sin(PI - ang);
	}
	if (ang > PI && ang < 3 * PI / 2)
	{
		coord->x = -cos(ang - PI);
		coord->y = sin(ang - PI);
	}
	if (ang > 3 * PI / 2 && ang < 2 * PI)
	{
		coord->x = cos(2 * PI - ang);
		coord->y = sin(2 * PI - ang);
	}
	return (*coord);
}

t_coord	get_wanted_move_dir_enemy(double ang)
{
	t_coord	coord;

	ft_memset(&coord, 0, sizeof(t_coord));
	if (ang == 0)
		coord.x = 1;
	if (ang == PI)
		coord.x = -1;
	if (ang == PI / 2)
		coord.y = -1;
	if (ang == 3 * PI / 2)
		coord.y = 1;
	if (ang > 0 && ang < PI / 2)
	{
		coord.x = cos(ang);
		coord.y = -sin(ang);
	}
	return (get_wanted_move_dir_enemy_p2(ang, &coord));
}

t_bool	is_valid_move_enemy(t_param *prm, t_coord pos)
{
	if (ft_strchr("123456789D", prm->map.map[(int)(pos.y)][(int)(pos.x)]))
		return (FALSE);
	return (TRUE);
}
