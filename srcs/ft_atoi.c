/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:48:10 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 13:01:33 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\n' || \
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			k;
	long int	res;

	i = 0;
	k = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (i > 0 && str[i - 1] == '-')
		k = -1;
	while (str[i] == 48)
		i++;
	while (str[i] != 0 && str[i] > 47 && str[i] < 58)
	{
		if (res > 214748364 && k == 1)
			return (-1);
		if (res > 214748364 && k == -1)
			return (0);
		res = (res * 10) + str[i] - 48;
		i++;
	}
	return (k * res);
}

int	ft_isnum(char c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

void	ft_win_win_dest(t_win *win)
{
	if (win->no_path != 0)
		mlx_destroy_image(win->mlx, win->no_path);
	if (win->so_path != 0)
		mlx_destroy_image(win->mlx, win->so_path);
	if (win->we_path != 0)
		mlx_destroy_image(win->mlx, win->we_path);
	if (win->ea_path != 0)
		mlx_destroy_image(win->mlx, win->ea_path);
	if (win->s_path != 0)
		mlx_destroy_image(win->mlx, win->s_path);
	if (win->img != 0)
		mlx_destroy_image(win->mlx, win->img);
	if (win->win != 0)
		mlx_destroy_window(win->mlx, win->win);
	if (win->mlx != 0)
		mlx_destroy_display(win->mlx);
	if (win->cub != 0)
		ft_free_cub(win->cub);
	free(win->mlx);
	free(win);
}
