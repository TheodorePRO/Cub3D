/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:17:27 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 12:31:41 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotation(int keycode, t_win *win)
{
	if (keycode == 65363)
	{
		win->cub->pa -= win->cub->rotspeed;
		if (win->cub->pa < 0)
			win->cub->pa = 2 * M_PI;
		win->dx = cos(win->cub->pa);
		win->dy = sin(win->cub->pa);
	}
	else if (keycode == 65361)
	{
		win->cub->pa += win->cub->rotspeed;
		if (win->cub->pa > (M_PI * 2))
			win->cub->pa = 0;
		win->dx = cos(win->cub->pa);
		win->dy = sin(win->cub->pa);
	}
}

// change setting and call image drowing
int	ft_move(int keycode, t_win *win)
{
	printf("keyevent: %d\n", keycode);
	if (keycode == 65362 || keycode == 'w')
		ft_actualmove(win, 1, -1, 0);
	else if (keycode == 65363 || keycode == 65361)
		ft_rotation(keycode, win);
	else if (keycode == 65364 || keycode == 's')
		ft_actualmove(win, -1, 1, 0);
	else if (keycode == 'a')
		ft_actualmove(win, -1, -1, 1);
	else if (keycode == 'd')
		ft_actualmove(win, 1, 1, 1);
	else if (keycode == 'm')
		win->map = (win->map + 1) % 3;
	else if (keycode == 65307)
		ft_win_destroy(win, 0, 0, 0);
	ft_draw_img(win);
	return (1);
}

void	ft_gameinit0(t_win *win)
{
	win->img = 0;
	win->no_path = 0;
	win->so_path = 0;
	win->ea_path = 0;
	win->we_path = 0;
	win->s_path = 0;
	win->win = 0;
	win->cub = 0;
	win->mlx = 0;
	win->map = 0;
	win->info = 0;
}

void	ft_gameinit(t_win *win)
{
	win->cub->bonus = 1;
	if (win->cub->xsize > 2000 || win->cub->xsize < 300)
		win->cub->xsize = 840;
	if (win->cub->ysize > 2000 || win->cub->ysize < 150)
		win->cub->ysize = 440;
	win->cub->rotspeed = 0.04;
	win->cub->map_size = 3;
	win->cub->angle_vue = 60;
	win->color = 0x00FF0000;
	win->rx = 0;
	win->ry = 0;
	win->dx = cos(win->cub->pa);
	win->dy = sin(win->cub->pa);
	win->prop = (win->cub->xsize / win->cub->map_size) / win->cub->mapx;
	if (win->prop > (win->cub->ysize / win->cub->map_size) / win->cub->mapy)
		win->prop = (win->cub->ysize / win->cub->map_size) / win->cub->mapy;
	if (win->no_path == 0 || win->so_path == 0 || win->ea_path == 0 || \
	win->we_path == 0)
		ft_win_destroy(win, "Manque texture", 0, 0);
}

int	main(int argc, char **argv)
{
	t_win	*win;

	checkargs(argc, argv);
	win = (t_win *)malloc(sizeof(t_win));
	if (win == 0)
		ft_win_destroy(0, "win malloc", errno, 0);
	ft_gameinit0(win);
	win->mlx = mlx_init();
	if (win->mlx == 0)
		ft_win_destroy(win, "mlx init", errno, 0);
	getcub(argv[1], win);
	ft_gameinit(win);
	win->win = mlx_new_window(win->mlx, win->cub->xsize, win->cub->ysize, \
	"CUB 3D Theodore");
	if (win->win == 0)
		ft_win_destroy(win, "img init", errno, 0);
	win->img = mlx_new_image(win->mlx, win->cub->xsize, win->cub->ysize);
	if (win->img == 0)
		ft_win_destroy(0, "Main pic_init(): can't load main pic", 0, 0);
	ft_draw_img(win);
	mlx_hook(win->win, 2, 1L << 0, &ft_move, win);
	mlx_hook(win->win, 28, 1L << 22, ft_draw_img, win);
	mlx_hook(win->win, 33, 1L << 17, ft_destroy_hook, win);
	mlx_loop(win->mlx);
	return (1);
}
