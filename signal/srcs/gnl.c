/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:14:44 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/10 17:03:18 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	test( int **r, char *buf)
{
	if (**r == -1)
		return (0);
	buf[**r] = 0;
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
int	test2( int **r, char *buf, char *str, int fd)
{
	if (ft_strchr(buf, '\n'))
		return (0);
	**r = read(fd, buf, BUFFER_SIZE);
	if (**r == -1)
		free(str);
	return (1);
}

char	*read_line(char *str, int fd, int *r, char *tmp)
{
	char	buf[BUFFER_SIZE + 1];

	*r = read(fd, &buf, BUFFER_SIZE);
	while (*r > 0)
	{
		if (test(&r, buf) == 0)
			return (str);
		if (str)
		{
			tmp = ft_strjoin(str, buf);
			free(str);
			if (tmp == NULL)
				return (NULL);
			str = ft_strdup(tmp);
			free(tmp);
		}
		else
			str = ft_strdup(buf);
		if (str == NULL)
			return (NULL);
		if (test2(&r, buf, str, fd) == 0)
			return (str);
	}
	return (str);
}

char	*minifree(char *str)
{
	free(str);
	return (NULL);
}

char	*get_line(char *str, char **line, int r)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (i < ft_strlen(str))
	{
		if (i == 0)
			i++;
		*line = ft_substr(str, 0, i);
		i--;
		if (*line == NULL)
			return (minifree(str));
		tmp = ft_substr(str, i + 1, ft_strlen(str));
		free(str);
		if (tmp == NULL)
			return (NULL);
		str = ft_strdup(tmp);
		free(tmp);
	}
	else if (r == 0)
	{
		*line = str;
		str = NULL;
	}
	return (str);
}

int	get_next_line(int fd, char **line)
{
	static char		*str;
	int				r;
	char			*tmp;

	tmp = NULL;
	if (fd < 0 || !line)
		return (-1);
	if (BUFFER_SIZE < 1)
		return (-1);
	str = read_line(str, fd, &r, tmp);
	if (str == NULL || r == -1)
		return (-1);
	str = get_line(str, line, r);
	if (r <= 0 && !str)
		return (r);
	// if (str == NULL)
	// 	return (-1);
	return (1);
}