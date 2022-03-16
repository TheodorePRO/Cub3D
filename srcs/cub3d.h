/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 22:15:18 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 13:03:14 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <errno.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include "gnl/get_next_line.h"

typedef struct s_pos {
	double		x;
	double		y;
}				t_pos;

typedef struct s_cub {
	int			f;
	int			c;
	char		**map;
	int			bonus;
	float		rotspeed;
	int			mapy;
	int			mapx;
	double		xpos;
	double		ypos;
	int			xsize;
	int			ysize;
	int			map_size;
	double		pa;
	char		texture;
	float		dist;
	float		xshort;
	float		yshort;
	float		xxshort;
	float		angle_vue;
}				t_cub;

typedef struct s_win {
	int		info;
	int		color;
	int		prop;
	t_cub	*cub;
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*no_path;
	t_img	*so_path;
	t_img	*we_path;
	t_img	*ea_path;
	t_img	*s_path;
	double	dx;
	double	dy;
	int		map;
	int		dof;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
}			t_win;

typedef struct s_ray {
	double		rra;
	double		rx;
	double		ry;
}			t_ray;

typedef struct s_line
{
	int			error;
	int			offset;
	int			sign_y;
	int			sign_x;
	int			delta_y;
	int			delta_x;
}				t_line;

int				ft_atoi(const char *str);
int				ft_game(t_cub *cub);
void			checkargs(int argc, char **argv);
void			getcub(char *argv, t_win *win);
void			getcub2(char *argv, t_win *win);
void			ft_checkmap(t_win *win);
void			ft_die2(int fd, t_cub *cub, char *err);
void			ft_print_ray(t_win *win, int mx, int my);
void			ft_print_ray2(t_win *win, int mx, int my);
void			ft_raycast1(t_win *win);
void			ft_raycast3(t_win *win, char texture);
void			ft_raycast2(t_win *win, float ra);
void			ft_win_destroy(t_win *win, char *errmsg, int errnu, char *line);
void			ft_free_cub(t_cub *cub);
int				ft_destroy_hook(t_win *win);
void			draw_pixel2(t_img *img, int x, int y, int color);
void			draw_player(t_win *win);
void			draw_ray(t_win *win);
void			getxpm(t_win *win, t_img **img, char *adr);
unsigned int	mlx_get_pixel(t_img *img, int x, int y);
void			ft_raycast0(t_win *win, float ra);
void			ft_register(float distv, char texture, t_win *win, int i);
void			ft_registerinfo(t_win *win, char *line);
int				ft_getpos(t_win *win, int i, int j, int pos);
int				ft_isinmapcol(char **map, int j, int i, int len);
int				ft_isinmaplin(char **map, int j, int i);
int				ft_is02nswe(char c);
int				ft_isnswe(char c);
int				ft_draw_img(t_win *win);
void			drawmap(t_win *win);
void			ft_drawvline(t_win *win, float lineh, int x);
void			ft_actualmove(t_win *win, int x, int y, int z);
int				ft_isnum(char c);
void			ft_errmess(t_win *win, char *line, char *msg);
void			ft_win_win_dest(t_win *win);

#endif
