/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 21:43:19 by tjudlin           #+#    #+#             */
/*   Updated: 2022/03/09 22:52:02 by tjudlin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_isdigit(char s)
{
	if (s > 47 && s < 58)
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strcadu(char *s1, char *s2, int b)
{
	int		i;
	int		j;
	char	*dup;

	i = ft_strlen(s1) + ft_strlen(s2);
	dup = (char *)malloc(sizeof(*dup) * (i + 1));
	if (!dup)
		return (0);
	i = -1;
	j = -1;
	while (s1[++i] != 0)
		dup[i] = s1[i];
	while (s2[++j] != 0)
		dup[i++] = s2[j];
	dup[i] = 0;
	if (b == 1)
	{
		free(s1);
		s1 = 0;
	}
	return (dup);
}

int	endline(char *buf)
{
	int	i;

	i = -1;
	while (buf[++i] != 0)
		if (buf[i] == '\n')
			return (i);
	return (-1);
}

void	ft_strback(char *buf, int c)
{
	int		j;

	j = -1;
	while (buf[c + ++j] != 0)
		buf[j] = buf[c + j];
	buf[j] = 0;
}
