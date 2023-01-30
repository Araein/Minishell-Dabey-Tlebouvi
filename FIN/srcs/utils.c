/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:37:17 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 21:07:35 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**to_return_or_not(char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!(tab))
		return (NULL);
	return (tab);
}

char	*get_s(char *s, int type)
{
	if (type == 1)
	{
		while (*s && *s == ' ' && *(s - 1) == ' ')
			s++;
	}
	else
	{
		while (*s && *s == ' ' && *(s - 1) == ' ')
			s++;
	}
	return (s);
}

char	**ft_split(char *s, char c, int i, int j)
{
	char	**tab;
	int		count;

	count = ft_count_word(s, c);
	tab = to_return_or_not(s, c);
	if (!tab)
		return (NULL);
	while (i < count)
	{
		j = 0;
		while (*s == ' ' || *s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_word(s, c) + 1));
		if (!tab[i])
			return (NULL);
		while (*s != c && *s != '\0')
		{
			s = get_s(s, 1);
			tab[i][j++] = *s++;
			s = get_s(s, 2);
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
