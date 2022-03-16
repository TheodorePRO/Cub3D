/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 08:44:17 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 12:32:42 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isnswe(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_is02nswe(char c)
{
	if (c == '0' || ft_isnswe(c))
		return (1);
	return (0);
}

int	ft_isinmaplin(char **map, int j, int i)
{
	int	test;

	test = i;
	while (test > 0)
	{
		if (ft_is02nswe(map[j][test]))
			test--;
		else
			break ;
	}
	if ((test == 0 && ft_is02nswe(map[j][test])) || map[j][test] != '1')
		return (0);
	test = i;
	while (map[j][test] != 0)
	{
		if (ft_is02nswe(map[j][test]))
			test++;
		else
			break ;
	}
	if (map[j][test] == 0 || map[j][test] != '1')
		return (0);
	return (1);
}

int	ft_isinmapcol(char **map, int j, int i, int len)
{
	int	test;

	test = j;
	while (test > 0 && ft_is02nswe(map[test][i]))
		test--;
	if (map[test][i] != '1')
		return (0);
	test = j;
	while (test < (len - 1) && ft_is02nswe(map[test][i]))
		test++;
	if (map[test][i] != '1')
		return (0);
	return (1);
}

int	ft_getpos(t_win *win, int i, int j, int pos)
{
	if (pos == 0)
	{
		pos = 1;
		win->cub->xpos = i + 0.5;
		win->cub->ypos = j + 0.5;
		if (win->cub->map[j][i] == 'N')
			win->cub->pa = M_PI / 2;
		if (win->cub->map[j][i] == 'S')
			win->cub->pa = M_PI * 1.5;
		if (win->cub->map[j][i] == 'E')
			win->cub->pa = M_PI * 2;
		if (win->cub->map[j][i] == 'W')
			win->cub->pa = M_PI;
	}
	else
		ft_win_destroy(win, "Trop de joueurs sur la carte", 0, 0);
	return (pos);
}
