/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:35:26 by tjudlin           #+#    #+#             */
/*   Updated: 2022/02/09 14:31:43 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*nl;
	int			ret;

	if (BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	nl = ft_strcadu("", buf, 0);
	while (endline(buf) == -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = 0;
		nl = ft_strcadu(nl, buf, 1);
		if (ret == 0)
		{
			*line = nl;
			return (0);
		}
	}
	ft_strback(buf, endline(buf) + 1);
	nl[endline(nl)] = 0;
	*line = nl;
	return (1);
}
