/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:16:26 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/09/15 18:29:04 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	closefd(int one, int two, int three)
{
	close(one);
	close(two);
	if (three != -1)
		close(three);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	p;

	l = ft_strlen(s1);
	p = ft_strlen(s2);
	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * ((l + p + 1)));
	if (!dest)
		return (NULL);
	while (++i < l)
	{
		dest[i] = s1[i];
	}
	while (++j < p)
	{
		dest[i] = s2[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
	return (1);
}
