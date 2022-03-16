/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:11:58 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/09 16:10:00 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_dist(float ax, float ay, float bx, float by)
{
	return (sqrtf((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	ft_raycast0(t_win *win, float ra)
{
	win->cub->texture = 0;
	win->dof = 0;
	win->cub->dist = 100000;
	if (ra > M_PI && ra < 2 * M_PI)
	{
		win->ry = (int)(win->cub->ypos) + 1;
		win->rx = (win->cub->ypos - win->ry) / tan(ra) + win->cub->xpos;
		win->yo = 1;
		win->xo = -win->yo / tan(ra);
		win->cub->texture = 'S';
	}
	if (ra < M_PI && ra > 0)
	{
		win->ry = (int)(win->cub->ypos) - 0.0001;
		win->rx = (win->cub->ypos - win->ry) / tan(ra) + win->cub->xpos;
		win->yo = -1;
		win->xo = -win->yo / tan(ra);
		win->cub->texture = 'N';
	}
	if (ra == 0 || ra == (float)M_PI)
		win->dof = win->cub->mapy;
	ft_raycast1(win);
}

// Ray horizontal
void	ft_raycast1(t_win *win)
{
	int	mx;
	int	my;

	while (win->ry >= 0 && win->rx >= 0 && win->ry < win->cub->mapy && win->rx \
	< ft_strlen(win->cub->map[(int)(win->ry)]) && win->dof < win->cub->mapy)
	{
		mx = (int)(win->rx);
		my = (int)(win->ry);
		if (mx >= 0 && my >= 0 && (my < win->cub->mapy) && \
		(mx < ft_strlen(win->cub->map[my])) && (win->cub->map[my][mx] == '1'))
		{
			win->dof = win->cub->mapy;
			win->cub->dist = ft_dist(win->cub->xpos, win->cub->ypos, \
				win->rx, win->ry);
			ft_register(0, 'A', win, 0);
		}
		else
		{
			win->dof += 1;
			win->rx += win->xo;
			win->ry += win->yo;
		}
	}
	win->dof = 0;
}

// Ray vertical
void	ft_raycast2(t_win *win, float ra)
{
	char	texture;

	texture = 0;
	if (ra > M_PI / 2 && ra < M_PI * 3 / 2)
	{
		win->rx = (int)(win->cub->xpos) - 0.0001;
		win->ry = (win->cub->xpos - win->rx) * tan(ra) + win->cub->ypos;
		win->xo = -1;
		win->yo = -win->xo * tan(ra);
		texture = 'W';
	}
	if (ra < M_PI / 2 || ra > M_PI * 3 / 2)
	{
		win->rx = (int)(win->cub->xpos) + 1;
		win->ry = (win->cub->xpos - win->rx) * tan(ra) + win->cub->ypos;
		win->xo = 1;
		win->yo = -win->xo * tan(ra);
		texture = 'E';
	}
	if (ra == (float)(M_PI / 2) || ra == (float)(M_PI * 3 / 2))
		win->dof = win->cub->mapx;
	ft_raycast3(win, texture);
}

void	ft_raycast3(t_win *win, char texture)
{
	float	distv;

	distv = 1000000;
	while (win->ry > 0 && win->rx >= 0 && win->ry < win->cub->mapy && win->rx \
	< ft_strlen(win->cub->map[(int)win->ry]) && win->dof < win->cub->mapx)
	{
		if (win->ry > 0 && win->rx >= 0 && ((int)(win->ry) < win->cub->mapy) \
		&& ((int)win->rx < ft_strlen(win->cub->map[(int)win->ry])) && \
		(win->cub->map[(int)win->ry][(int)win->rx] == '1'))
		{
			win->dof = win->cub->mapx;
			distv = ft_dist(win->cub->xpos, win->cub->ypos, win->rx, win->ry);
			if (win->cub->dist > distv)
				ft_register(distv, texture, win, 1);
		}
		else
		{
			win->dof += 1;
			win->rx += win->xo;
			win->ry += win->yo;
		}
	}
}
