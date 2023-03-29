/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:46:52 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/29 20:18:09 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef enum e_bool {
	TRUE = 1,
	FALSE = 0
}				t_bool;

typedef enum e_dir {
	SOUTH = 1,
	NORTH,
	EAST,
	WEST,
	SOUTH_DOOR,
	NORTH_DOOR,
	EAST_DOOR,
	WEST_DOOR
}				t_dir;

typedef enum e_door_status {
	CLOSED = 0,
	OPENED,
	CLOSING,
	OPENING
}				t_door_status;

typedef struct s_coord {
	double	x;
	double	y;
}				t_coord;

typedef struct s_px_col
{
	int				px_cell;
	int				px_wall;
	int				px_total;
	int				px_open;
	int				ofset;
	int				color_cell;
	int				color_floor;
}					t_px_col;

typedef struct s_point {
	int	x;
	int	y;
	int	color;
}				t_point;

typedef struct s_seg {
	t_point	start;
	t_point	end;
}				t_seg;

typedef struct s_img {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_layer {
	t_img	front;
	t_img	back;
}				t_layer;

typedef struct s_key_stat {
	char	left;
	char	right;
	char	key_w;
	char	key_a;
	char	key_d;
	char	key_s;
	char	key_space;
}				t_key_stat;

typedef struct s_garb
{
	void			*ptr;
	int				id;
	struct s_garb	*next;
}					t_garb;

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
	t_img	north_texture;
	t_img	south_texture;
	t_img	west_texture;
	t_img	east_texture;
	t_img	door_texture;
	int		floor_color;
	int		ceiling_color;
}					t_map;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_status	status;
	int				percent_open;
	int				count_open;
}					t_door;

typedef struct s_param {
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			frame;
	t_img		*img_tab[128];
	int			in_focus;
	t_layer		layer;
	t_key_stat	key;
	t_map		map;
	t_coord		pos_player;
	t_coord		view_dir;
	t_coord		screen_dir;
	double		view_ang;
	t_garb		*garb;
	t_img		mini_map;
	t_door		**tab_doors;
	int			mm_res_x;
	int			mm_res_y;
}				t_param;

#endif
