/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 22:59:14 by abelarif          #+#    #+#             */
/*   Updated: 2020/02/07 19:56:22 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_all(char *buf, char **rest)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	if (*rest)
	{
		free(*rest);
		*rest = NULL;
	}
	return (NULL);
}

int		ft_checkvalue(int read_value, char **line, char *rest)
{
	static int i = 0;

	if (read_value < 0)
		return (-1);
	else if (read_value == 0 && i == 0)
	{
		*line = rest;
		i++;
		free(rest);
		return (0);
	}
	else if (read_value == 0 && i > 0)
		*line = "";
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			read_value;
	static char	*rest = "";
	int			index_nl;
	char		*buf;

	index_nl = -1;
	if (fd < 0 || BUFFER_SIZE < 0 || !line || !(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (1)
	{
		if ((index_nl = check_nl(rest)) >= 0)
		{
			*line = r_l(rest, index_nl);
			return ((!(*line) || !(rest = r_r(rest, index_nl))) ? -1 : 1);
		}
		if (index_nl < 0)
		{
			if ((read_value = read(fd, buf, BUFFER_SIZE)) <= 0)
				return (ft_checkvalue(read_value, line, rest));
				buf[read_value] = '\0';
			rest = strjoin(&rest, buf);
		}
	}
}


int		main(void)
{
	int		fd;
	int		i;
	char	*line;
	int		l;

	i = 1;
	l = 1;
	fd = open("bar.txt", O_RDONLY);
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (i > 0)
			printf("%s\n", line);
		else
			printf("%s", line);
		//free(line);
		l++;
	}
	return (0);
}
