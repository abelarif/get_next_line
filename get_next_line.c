/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 22:59:14 by abelarif          #+#    #+#             */
/*   Updated: 2020/01/24 19:00:23 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*my_free(char *buf, char *rest)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	if (rest)
	{
		free(rest);
		rest = NULL;
	}
	return (NULL);
}

int	ft_checkvalue(int read_value, char **line, char *rest)
{
	if (read_value < 0)
		return (-1);
	if (read_value == 0)
		*line = rest;
	return (0);
}

int	get_next_line(int fd, char **line)
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
			return((!(*line = r_l(rest, index_nl)) || !(rest = r_r(rest,
			index_nl))) ? -1 : 1);
		if (index_nl < 0)
		{
			if ((read_value = read(fd, buf, BUFFER_SIZE)) <= 0)
				return (ft_checkvalue(read_value, line, rest));
			buf[read_value] = '\0';
			rest = strjoin(rest, buf);
		}
	}
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;
	int		l;
	i = 1;
	l = 1;
	fd = open("get_next_line.c", O_RDONLY);
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		printf("%d | %d | %s\n",l , i, line);
		l++;
	}
	return (0);
}
/*
size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	check_nl(const char *rest)
{
	int i;

	i = 0;
	while (rest[i])
	{
		if (rest[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*strjoin(char *rest, char *buf)
{
	int		lenrest;
	int		lenbuf;
	char	*p;
	int		i;
	int		j;

	if (rest == 0)
		return (buf);
	lenbuf = ft_strlen(buf);
	lenrest = ft_strlen(rest);
	if (!(p = malloc((lenrest + lenbuf + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (++i < lenrest)
		p[i] = rest[i];
	j = 0;
	while (i < (lenrest + lenbuf))
		p[i++] = buf[j++];
	p[i] = '\0';
	return (p);
}

char	*r_r(char *rest, int index_nl)
{
	char	*r;
	int		i;

	i = 0;
	if (!(r = malloc(sizeof(char) * (ft_strlen(rest) - index_nl))))
		return (0);
	while ((index_nl + 1) < (int)ft_strlen(rest))
	{
		r[i] = rest[index_nl + 1];
		i++;
		index_nl++;
	}
	r[i] = '\0';
	return (r);
}

char	*r_l(char *rest, int index_nl)
{
	char	*l;
	int		i;

	i = 0;
	if (!(l = malloc(sizeof(char) * (index_nl + 1))))
		return (0);
	while (i < index_nl)
	{
		l[i] = rest[i];
		i++;
	}
	l[i] = '\0';
	return (l);
}
*/