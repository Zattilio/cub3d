/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/04/08 14:30:24 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	put_img_to_front(t_param *prm, t_img *xpm, int dx, t_coord sprite)
{
	t_boundary	b;
	int			ret;

	ret = 0;
	init_col_px_sprite(prm, sprite, &b.col);
	init_boundary(prm, xpm, &b, dx);
	while (b.i.x < b.stop.x - b.offset_stop.x
		&& b.i.x >= 0 && b.i.x < prm->width)
	{
		b.i.y = b.start.y + b.offset_start.y;
		if (check_distance_x(prm, sprite, b.i))
		{
			while (b.i.y < b.stop.y - b.offset_stop.y
				&& b.i.y >= 0 && b.i.y < prm->height)
			{
				ret += put_on_one_pixel(prm, xpm, b, sprite);
				b.i.y++;
			}
		}
		b.i.x++;
	}
	return (ret);
}

double	get_angle_with_player_view(t_param *prm, t_coord sprite)
{
	return (convert_angle(-atan2((sprite.y - prm->pos_player.y),
				sprite.x - prm->pos_player.x)));
}

static void	explode(t_param *prm, t_sprite *sprite)
{
	t_list	*current;

	current = prm->sprite_lst;
	while (current)
	{
		if (current->content != sprite
			&& get_distance(((t_sprite *)current->content)->coord,
				sprite->coord) < 1.5
			&& ((t_sprite *)current->content)->health != 0)
			((t_sprite *)current->content)->health--;
		current = current->next;
	}
	if (get_distance(sprite->coord, prm->pos_player) < 1.5)
		prm->n_life--;
}

void	ai_enemies(t_param *prm, t_sprite *sprite, int seen)
{
	static int	has_been_seen = 0;
	static int	shooting = 0;

	if (seen)
		has_been_seen = 50000;
	if (sprite->type == 'R' && has_been_seen && !sprite->ok_to_shoot)
	{
		sprite->follow = TRUE;
		has_been_seen--;
	}
	if (sprite->type == 'R' && seen
		&& get_distance_square(sprite->coord, prm->pos_player) < SHOOT_DST_SQ
		&& sprite->health > 0)
	{
		sprite->ok_to_shoot = TRUE;
		sprite->follow = FALSE;
		shooting++;
		if (shooting > 40)
		{
			shooting = 0;
			prm->n_life--;
		}
	}
	else
		sprite->ok_to_shoot = FALSE;
}

void	do_gun_damage(t_param *prm, t_sprite *sprite, double theta, int seen)
{
	if ((sprite->type == 'B' || sprite->type == 'R') && seen
		&& (prm->gun.frame_count == 1 && sprite->health > 0)
		&& convert_angle(prm->view_ang - theta - PI / 2) >= PI
		&& convert_angle(v_abs_dbl(prm->view_ang - theta)) <= SHOOT_ANG)
	{
			sprite->health--;
	}
}

void	kill_baril(t_param *prm, t_sprite *sprite, double theta, int dx)
{
	if (sprite->health == 0 && sprite->type == 'B')
	{
		if (convert_angle(prm->view_ang - theta - PI / 2) >= PI)
			put_img_to_front(prm, &prm->gun.explo[sprite->frame],
				dx, sprite->coord);
		sprite->frame++;
		if (sprite->frame == 7)
		{
			sprite->dead = 1;
			explode(prm, sprite);
		}
		prm->map.map[(int)sprite->coord.y][(int)sprite->coord.x] = '0';
	}
}

void	kill_enemies(t_param *prm, t_sprite *sprite, double theta, int dx)
{
	if (sprite->health == 0 && sprite->type == 'R')
	{
		if (convert_angle(prm->view_ang - theta - PI / 2) >= PI)
			put_img_to_front(prm, &prm->map.die_texture[sprite->frame / 2],
				dx, sprite->coord);
		if (sprite->frame < 3 * 2)
			sprite->frame++;
		sprite->dead = 1;
	}
}

static void	print_sprite(t_param *prm, t_sprite *sprite, t_img *xpm)
{
	double	theta;
	int		dx;
	int		seen;

	dx = 0;
	theta = get_angle_with_player_view(prm, sprite->coord);
	dx = (int)nearbyint((tan(convert_angle(prm->view_ang - theta))
				* prm->width) / (2 * 0.5773502)) + (prm->width / 2);
	if (!sprite->dead && convert_angle(prm->view_ang - theta - PI / 2) >= PI)
		seen = put_img_to_front(prm, xpm, dx, sprite->coord);
	ai_enemies(prm, sprite, seen);
	do_gun_damage(prm, sprite, theta, seen);
	kill_baril(prm, sprite, theta, dx);
	kill_enemies(prm, sprite, theta, dx);
}

void	print_every_sprite(t_param *prm)
{
	t_list		*current;
	t_sprite	*sprite;

	current = prm->sprite_lst;
	ft_lstsort(prm, current, &cmp_distance);
	while (current)
	{
		sprite = (t_sprite *)current->content;
		if (sprite->type == 'B' && !sprite->dead)
			print_sprite(prm, sprite, &prm->map.barrel_texture);
		if (sprite->type == 'C')
			print_sprite(prm, sprite, &prm->map.cables_texture);
		if (sprite->type == 'R')
		{
			if (sprite->follow)
				print_sprite(prm, sprite,
					&prm->map.front_texture[prm->frame / 4 % 4]);
			else if (sprite->ok_to_shoot)
				print_sprite(prm, sprite,
					&prm->map.attack_texture[prm->frame / 4 % 4]);
			else
				print_sprite(prm, sprite, &prm->map.front_texture[0]);
		}
		current = current->next;
	}
}
