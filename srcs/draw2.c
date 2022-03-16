/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:22:34 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/09 23:00:52 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_getimg(t_win *win)
{
	if (win->cub->texture == 'N')
		return (win->no_path);
	if (win->cub->texture == 'S')
		return (win->so_path);
	if (win->cub->texture == 'W')
		return (win->we_path);
	if (win->cub->texture == 'E')
		return (win->ea_path);
	return (0);
}

float	ft_getoffset(t_win *win, float lineh)
{
	float	offset;

	offset = 0;
	if (lineh > win->cub->ysize)
		offset = (lineh - win->cub->ysize) / 2;
	return (offset);
}

//Draw vertline
void	ft_drawvline(t_win *win, float lineh, int x)
{
	float	offset;
	float	step;
	int		color;
	int		i;
	t_img	*texture;

	offset = ft_getoffset(win, lineh);
	step = win->cub->ysize / (float)lineh;
	if (lineh > win->cub->ysize)
		lineh = win->cub->ysize;
	texture = ft_getimg(win);
	i = 0;
	while (i < (win->cub->ysize - lineh) / 2)
		draw_pixel2(win->img, x, i++, win->cub->c);
	while (i <= (win->cub->ysize + lineh) / 2)
	{
		if (texture != 0)
			color = mlx_get_pixel(texture, (int)(win->cub->xxshort * \
			win->cub->xsize) % texture->width, (int)((i - (win->cub->ysize - \
			lineh) / 2 + offset) * step) % texture->height);
		draw_pixel2(win->img, x, i++, color);
	}
	while (i < win->cub->ysize)
		draw_pixel2(win->img, x, i++, win->cub->f);
}

void	drawmap(t_win *win)
{
	int	i;
	int	j;

	j = -1;
	while (++j < win->cub->ysize)
	{
		i = -1;
		while (++i < win->cub->xsize)
		{
			if ((j / win->prop < win->cub->mapy) && \
				(i / win->prop < ft_strlen(win->cub->map[j / win->prop])) && \
				(win->cub->map[j / (win->prop)][i / (win->prop)] == '1'))
			{
				draw_pixel2(win->img, i, j, win->color);
			}
		}
	}
}

void	ft_register(float distv, char texture, t_win *win, int i)
{
	if (i == 1)
	{
		win->cub->dist = distv;
		win->cub->texture = texture;
		win->cub->xshort = win->rx;
		win->cub->xxshort = win->ry;
		win->cub->yshort = win->ry;
	}
	else if (i == 0)
	{
		win->cub->xshort = win->rx;
		win->cub->xxshort = win->rx;
		win->cub->yshort = win->ry;
	}
}
