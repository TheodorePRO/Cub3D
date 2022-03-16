/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:27:34 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 13:33:03 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checkargs(int ac, char **av)
{
	int		i;
	char	*cub;

	if (ac != 2)
		ft_die2(0, 0, "Problème nombre d'arguments");
	i = 0;
	cub = ".cub";
	while (++i < 4)
		if (av[1][ft_strlen(av[1]) - i] != cub[4 - i])
			ft_die2(0, 0, "Problème argument "".cub""");
}

void	ft_texture(t_win *win, t_img **img, char *adr)
{
	int	width;
	int	height;
	int	i;

	if (win->info < 6)
		win->info++;
	else
		ft_win_destroy(win, "Too many info", 0, adr - 3);
	i = 0;
	while (adr[i] == ' ')
		i++;
	*img = mlx_xpm_file_to_image(win->mlx, adr + i, &width, &height);
	if (*img == 0)
		ft_win_destroy(win, "texture_init : can't load texture", errno, adr -3);
	(*img)->width = width;
	(*img)->height = height;
}

unsigned int	ft_getrgb(t_win *win, char *line, int nb, char c)
{
	unsigned int	col;

	col = 0;
	while (line[nb] && line[nb] == ' ')
		nb++;
	if (ft_isnum(line[nb]) == 0)
		ft_win_destroy(win, "Colour missing", 1, line);
	while (line[nb] && ft_isnum(line[nb]) == 1)
	{
		col = col * 10 + (line[nb] - 48);
		nb++;
	}
	if (col > 255)
		ft_win_destroy(win, "Colour code too big", 1, line);
	while (line[nb] && line[nb] == ' ')
		nb++;
	if (line[nb] != c)
		ft_win_destroy(win, "Colour code not as expected", 1, line);
	return (col);
}

unsigned int	ft_getcolor(char *line, t_win *win)
{
	int	col;
	int	cols;
	int	i;

	if (win->info > 5)
		ft_win_destroy(win, "Too many infos", 1, line);
	win->info++;
	cols = -1;
	i = 1;
	col = ft_getrgb(win, line, i, ',');
	cols = 256 * 256 * col;
	while (line[i] && line[i] != ',')
		i++;
	col = ft_getrgb(win, line, i + 1, ',');
	cols = cols + (256 * col);
	i++;
	while (line[i] && line[i] != ',')
		i++;
	col = ft_getrgb(win, line, i + 1, 0);
	cols = cols + col;
	while (line[i] && line[i] == ' ')
		i++;
	return ((unsigned int)cols);
}

void	ft_registerinfo(t_win *win, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		ft_texture(win, &win->no_path, &line[3]);
	else if (line[0] == 'S' && line[1] == 'O')
		ft_texture(win, &win->so_path, &line[3]);
	else if (line[0] == 'W' && line[1] == 'E')
		ft_texture(win, &win->we_path, &line[3]);
	else if (line[0] == 'E' && line[1] == 'A')
		ft_texture(win, &win->ea_path, &line[3]);
	else if (line[0] == 'F')
		win->cub->f = ft_getcolor(line, win);
	else if (line[0] == 'C')
		win->cub->c = ft_getcolor(line, win);
}
