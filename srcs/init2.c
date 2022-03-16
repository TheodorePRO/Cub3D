/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:02:11 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 12:21:38 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_registersize(t_win *win, char *line)
{
	int		i;

	if (line[0] == 'R' && line[1] == ' ')
	{
		i = 2;
		while (line[i] == ' ')
			i++;
		win->cub->xsize = ft_atoi(&line[i]);
		while (line[i] != 0 && ft_isdigit(line[i]))
			i++;
		if (line[i] != 0)
			win->cub->ysize = ft_atoi(&line[i]);
	}
}

int	ft_registermap(t_win *win, char *line)
{
	int		i;
	int		nbl;

	nbl = 0;
	if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1' || line[i] == '0')
		{
			if (win->info < 6)
				ft_win_destroy(win, "The map shall be last", 0, line);
			win->info++;
			nbl++;
			if (win->cub->mapx < (int)ft_strlen(line))
				win->cub->mapx = (int)ft_strlen(line);
		}
		else if (line[i] != 0 && win->info > 6)
			ft_win_destroy(win, "the map is broken", 0, line);
	}
	else if (win->info > 6)
		ft_win_destroy(win, "the map is broken", 0, line);
	return (nbl);
}

void	getcub(char *argv, t_win *win)
{
	int		fd;
	int		nbl;
	char	*line;

	win->cub = (t_cub *)malloc(sizeof (t_cub));
	if (win->cub == 0)
		ft_win_destroy(win, "Problème mémoire cub, fin", errno, 0);
	win->cub->map = 0;
	win->cub->mapx = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_win_destroy(win, "Problème d'ouverture de fichier", errno, 0);
	nbl = 0;
	while (get_next_line(fd, &line))
	{
		ft_registerinfo(win, line);
		ft_registersize(win, line);
		nbl += ft_registermap(win, line);
		free(line);
	}
	free(line);
	close(fd);
	win->cub->mapy = nbl;
	getcub2(argv, win);
}

int	ft_getmap(t_cub *cub, int fd, char *line)
{
	int		j;
	int		i;
	int		k;

	j = -1;
	k = get_next_line(fd, &line);
	while (k > 0)
	{
		if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
		{
			i = 0;
			while (line[i] == ' ')
				i++;
			if (line[i] == '1' || line[i] == '0')
				cub->map[++j] = line;
			else
				free(line);
		}
		else
			free(line);
		k = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return (k);
}

void	getcub2(char *argv, t_win *win)
{
	int		fd;
	int		k;
	char	*line;

	line = 0;
	fd = open(argv, O_RDONLY);
	win->cub->map = (char **)malloc(sizeof (char *) * win->cub->mapy);
	if (win->cub->f == -1 || win->cub->c == -1 || !win->cub->map || fd == -1)
		ft_win_destroy(win, "Problème get CUB2 fin des opérations", errno, 0);
	k = ft_getmap(win->cub, fd, line);
	if (k == -1)
		ft_win_destroy(win, "Problème gnl de map, fin", errno, 0);
	close(fd);
	ft_checkmap(win);
}
