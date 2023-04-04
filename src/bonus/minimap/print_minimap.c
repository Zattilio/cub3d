/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:34:55 by mbocquel          #+#    #+#             */
/*   Updated: 2023/04/04 19:00:29 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initiate_img_minimap(t_param *prm)
{
	prm->mm_res_x = 6;
	prm->mm_res_y = 6;
	prm->mini_map.width = 200;
	prm->mini_map.height = 200;
	prm->mini_map.img = mlx_new_image(prm->mlx, prm->mini_map.width,
			prm->mini_map.height);
	prm->mini_map.addr = mlx_get_data_addr(prm->mini_map.img,
			&(prm->mini_map.bits_per_pixel), &(prm->mini_map.line_length),
			&(prm->mini_map.endian));
}

void	print_mini_map_grid(t_param *prm)
{
	t_point	p;
	int		color;

	p.x = 0;
	color = create_trgb(0, 125, 125, 125);
	while (p.x < prm->mini_map.width)
	{
		p.y = -1;
		while (++(p.y) < prm->mini_map.height)
			my_mlx_pixel_put(&(prm->mini_map), p.x, p.y, color);
		p.x += prm->mm_res_x;
	}
	p.y = 0;
	while (p.y < prm->mini_map.height)
	{
		p.x = -1;
		while (++(p.x) < prm->mini_map.width)
			my_mlx_pixel_put(&(prm->mini_map), p.x, p.y, color);
		p.y += prm->mm_res_y;
	}
}

void	print_minimap(t_param *prm)
{
	t_point	p;
	double	res;
	t_point	p_distance;
	t_point	middle;
	t_coord	new_orig;
	t_coord	coord;
	double	d_min;
	
	p_distance.x = prm->mini_map.width / 2;
	p_distance.y = 0;
	middle.x = prm->mini_map.width / 2;
	middle.y = prm->mini_map.height / 2;
	//res = prm->mini_map.width / 10;
	res = 10;
	new_orig.x = prm->pos_player.x - (double)(prm->mini_map.width / 2) / res;
	new_orig.y = prm->pos_player.y - (double)(prm->mini_map.height / 2) / res;
	d_min = get_distance_point(p_distance, middle);
	p.x = -1;
	while (++p.x < prm->mini_map.width)
	{
		p.y = -1;
		while (++p.y < prm->mini_map.height)
		{
			coord.x = new_orig.x + (double)p.x / res;
			coord.y = new_orig.y + (double)p.y / res;
			if (get_distance_point(p, middle) <= d_min)
			{
				if (!is_valid_coord(prm, coord)
				|| (ft_strchr("13456789", prm->map.map[(int)coord.y][(int)coord.x])))
					my_mlx_pixel_put(&(prm->mini_map), p.x, p.y,
						create_trgb(0, 0, 0, 0));
				else if (is_valid_coord(prm, coord) && prm->map.map[(int)coord.y][(int)coord.x] == 'D')
					my_mlx_pixel_put(&(prm->mini_map), p.x, p.y,
						create_trgb(0, 0, 0, 255));
				else
					my_mlx_pixel_put(&(prm->mini_map), p.x, p.y,
						create_trgb(0, 255, 255, 255));
			}
			else
				my_mlx_pixel_put(&(prm->mini_map), p.x, p.y,
					create_trgb(255, 0, 0, 0));
		}
	}
	print_player(prm);
}
/*
void	print_minimap(t_param *prm)
{
	t_point	p;

	p.x = -1;
	while (++p.x < prm->mini_map.width)
	{
		p.y = -1;
		while (++p.y < prm->mini_map.height)
		{
			if (ft_strchr("13456789",
					prm->map.map[p.y / prm->mm_res_y][p.x / prm->mm_res_x])
				&& p.x < prm->mini_map.width && p.y < prm->mini_map.height)
				my_mlx_pixel_put(&(prm->mini_map), p.x, p.y,
					create_trgb(0, 78, 22, 9));
			else if (prm->map.map[p.y / prm->mm_res_y][p.x / prm->mm_res_x]
				== 'D' && p.x < prm->mini_map.width && p.y
					< prm->mini_map.height)
				my_mlx_pixel_put(&(prm->mini_map), p.x, p.y,
					create_trgb(0, 0, 0, 255));
			else
				my_mlx_pixel_put(&(prm->mini_map), p.x, p.y,
					create_trgb(0, 237, 237, 237));
		}
	}
	print_player(prm);
}*/

void	print_player(t_param *prm)
{
	t_point	del;
	t_point	p;
	int		size;

	p.x = prm->mini_map.width / 2;
	p.y = prm->mini_map.height / 2;
	p.color = create_trgb(0, 0, 0, 255);
	size = 3;
	del.x = p.x - size;
	while (del.x <= p.x + size)
	{
		del.y = p.y - size;
		while (del.y <= p.y + size)
		{
			if (del.x >= 0 && del.x < prm->mini_map.width && del.y >= 0
				&& del.y < prm->mini_map.height)
				my_mlx_pixel_put(&(prm->mini_map), del.x, del.y, p.color);
			del.y++;
		}
		del.x++;
	}
}


/*void	print_player(t_param *prm)
{
	t_point	del;
	t_point	p;

	p = get_minimap_pos(prm, prm->pos_player, create_trgb(0, 255, 0, 0));
	del.x = p.x - 2;
	while (del.x <= p.x + 2)
	{
		del.y = p.y - 2;
		while (del.y <= p.y + 2)
		{
			if (del.x >= 0 && del.x < prm->mini_map.width && del.y >= 0
				&& del.y < prm->mini_map.height)
				my_mlx_pixel_put(&(prm->mini_map), del.x, del.y, p.color);
			del.y++;
		}
		del.x++;
	}
	put_segment_img(&(prm->mini_map), p,
		get_minimap_pos(prm, sum_vect(prm->pos_player,
				prod_vect(0.7, prm->view_dir)), p.color));
}*/

void	print_raytracing(t_param *prm)
{
	double	ray_ang;
	int		color;

	color = create_trgb(0, 0, 0, 255);
	ray_ang = prm->view_ang - 30 * ((2 * PI) / 360);
	while (ray_ang < prm->view_ang + 30 * ((2 * PI) / 360))
	{
		put_segment_img(&(prm->mini_map),
			get_minimap_pos(prm, prm->pos_player, color),
			get_minimap_pos(prm,
				find_wall(prm, convert_angle(ray_ang)), color));
		ray_ang += (2 * PI) / 360;
	}
}
