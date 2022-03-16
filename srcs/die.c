/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:03:34 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/16 13:34:35 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_cub(t_cub *cub)
{
	int	i;

	i = -1;
	if (cub->map != 0)
	{
		while (++i < cub->mapy)
		{
			free(cub->map[i]);
			cub->map[i] = NULL;
		}
		free(cub->map);
		cub->map = NULL;
	}
	free(cub);
	cub = NULL;
}

void	die(char *errmsg, int errnum)
{
	if (errmsg != 0 || errnum != 0)
		printf("Error\n");
	if (errmsg != 0)
		perror(errmsg);
	if (errmsg == 0 && errnum != 0)
		perror("1 :");
	if (errmsg != 0 || errnum != 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	ft_win_destroy(t_win *win, char *errmsg, int errnum, char *line)
{
	if (line != 0)
		free(line);
	if (win != 0)
		ft_win_win_dest(win);
	die(errmsg, errnum);
}

int	ft_destroy_hook(t_win *win)
{
	ft_win_destroy(win, 0, 0, 0);
	return (0);
}

void	ft_die2(int fd, t_cub *cub, char *err)
{
	if (cub)
		ft_free_cub(cub);
	if (fd)
		close(fd);
	printf("Error\n%s\n", err);
	exit(EXIT_FAILURE);
}
