/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:25:31 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 12:25:46 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw60(t_win *win)
{
	int		i;
	float	ra;
	float	ri;
	float	lineh;

	i = -1;
	while (++i < win->cub->xsize)
	{
		ri = ((float)(win->cub->xsize / 2 - i) * win->cub->angle_vue / \
			win->cub->xsize * M_PI / 180);
		ra = win->cub->pa + ri;
		if (ra < 0)
			ra += 2 * M_PI;
		if (ra > 2 * M_PI)
			ra -= 2 * M_PI;
		ft_raycast0(win, ra);
		ft_raycast2(win, ra);
		if (win->map == 2)
			draw_ray(win);
		lineh = win->cub->ysize / (win->cub->dist * cos(ri));
		ft_drawvline(win, lineh, i);
	}
}

int	ft_draw_img(t_win *win)
{
	t_img	*img;
	t_img	*imgold;

	img = mlx_new_image(win->mlx, win->cub->xsize, win->cub->ysize);
	if (img == 0)
		ft_win_destroy(0, "Main pic_init(): can't load main pic", errno, 0);
	(*img).width = win->cub->xsize;
	(*img).height = win->cub->ysize;
	imgold = win->img;
	win->img = img;
	ft_draw60(win);
	if (win->map != 0)
	{
		drawmap(win);
		draw_player(win);
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	mlx_destroy_image(win->mlx, imgold);
	imgold = 0;
	return (0);
}

void	ft_stayin(t_win *win)
{
	if (win->cub->xpos < 0)
		win->cub->xpos = 0;
	if (win->cub->ypos < 0)
		win->cub->ypos = 0;
	if (win->cub->xpos > win->cub->xsize / win->prop)
		win->cub->xpos = win->cub->xsize / win->prop;
	if (win->cub->ypos > win->cub->ysize / win->prop)
		win->cub->ypos = win->cub->ysize / win->prop;
}

// collision
void	ft_actualmove(t_win *win, int x, int y, int z)
{
	if (z == 0)
	{
		if (!(win->cub->bonus == 1 && win->cub->map[(int)(win->cub->ypos)][\
		(int)(win->cub->xpos + x * (1.8 * win->dx / win->prop))] == '1'))
			win->cub->xpos += x * win->dx / win->prop;
		if (!(win->cub->bonus == 1 && win->cub->map[(int)(win->cub->ypos + y \
		* (1.8 * win->dy / win->prop))][(int)(win->cub->xpos)] == '1'))
			win->cub->ypos += y * win->dy / win->prop;
	}
	else
	{
		if (!(win->cub->bonus == 1 && win->cub->map[(int)(win->cub->ypos)][\
		(int)(win->cub->xpos + x * (1.8 * win->dy / win->prop))] == '1'))
			win->cub->xpos += x * win->dy / win->prop;
		if (!(win->cub->bonus == 1 && win->cub->map[(int)(win->cub->ypos + y \
		* (1.8 * win->dx / win->prop))][(int)(win->cub->xpos)] == '1'))
			win->cub->ypos += y * win->dx / win->prop;
	}
	ft_stayin(win);
}

void	ft_checkmap(t_win *win)
{
	int	i;
	int	j;
	int	pos;

	j = -1;
	pos = 0;
	while (++j < win->cub->mapy)
	{
		i = -1;
		while (win->cub->map[j][i + 1] == ' ')
			i++;
		while (win->cub->map[j][++i] != 0)
		{
			if (ft_is02nswe(win->cub->map[j][i]))
			{
				if (ft_isnswe(win->cub->map[j][i]))
					pos = ft_getpos(win, i, j, pos);
				if (!(ft_isinmaplin(win->cub->map, j, i)) || \
				!(ft_isinmapcol(win->cub->map, j, i, win->cub->mapy)))
					ft_win_destroy(win, "La carte donne sur le vide", 0, 0);
			}
		}
	}
	if (pos == 0)
		ft_win_destroy(win, "Pas de joueur sur la carte", 0, 0);
}
