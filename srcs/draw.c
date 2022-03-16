/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:07:46 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 13:01:14 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel2(t_img *img, int x, int y, int color)
{
	char			*target;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
	target = img->data + (x * img->bpp / 8 + y * img->size_line);
	*(unsigned int *)target = color;
	}
}

// Draw player
void	draw_player(t_win *win)
{
	int	i;
	int	j;

	j = -2;
	while (++j < 2)
	{
		i = -2;
		while (++i < 2)
			draw_pixel2(win->img, (win->cub->xpos * win->prop) + i, \
			(win->cub->ypos * win->prop) + j, 0x0000FF000);
	}
	i = -1;
	while (++i <= 5)
		draw_pixel2(win->img, win->prop * win->cub->xpos + i * win->dx, \
		win->prop * win->cub->ypos - i * win->dy, 0x0000FF000);
}

//Draw ray
void	draw_ray(t_win *win)
{
	t_pos	p1_temp;
	t_pos	p2_temp;
	double	step;
	double	i;

	p2_temp.x = win->prop * (win->cub->xshort - win->cub->xpos);
	p2_temp.y = win->prop * (win->cub->yshort - win->cub->ypos);
	if (fabs(p2_temp.x) >= fabs(p2_temp.y))
		step = fabs(p2_temp.x);
	else
		step = fabs(p2_temp.y);
	p2_temp.x = p2_temp.x / step;
	p2_temp.y = p2_temp.y / step;
	p1_temp.x = win->cub->xpos * win->prop;
	p1_temp.y = win->cub->ypos * win->prop;
	i = 0;
	while (i <= step)
	{
		draw_pixel2(win->img, p1_temp.x, p1_temp.y, 0x0000FF);
		p1_temp.x += p2_temp.x;
		p1_temp.y += p2_temp.y;
		i++;
	}
}

unsigned int	mlx_get_pixel(t_img *img, int x, int y)
{
	return (*(unsigned int *)
		(img->data + (x * img->bpp / 8 + y * img->size_line)));
}
