/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:37:17 by dabey             #+#    #+#             */
/*   Updated: 2023/01/26 12:27:30 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count_w;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	count_w = ft_count_word(s, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*s == ' ' || *s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_word(s, c) + 1));
		if (!tab[i])
			return (NULL);
		while (*s != c && *s != '\0')
		{
			while (*s && *s == ' ' && *(s - 1) == ' ')
				s++;
			tab[i][j++] = *s++;
			while (*s && *s == ' ' && *(s - 1) == ' ')
				s++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
