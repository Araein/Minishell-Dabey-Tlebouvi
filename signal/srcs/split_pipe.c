/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:01:32 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 21:32:00 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_word(char *s, char sep, char c)
{
	int		count_w;

	count_w = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			c = *s;
			s++;
			while (*s && *s != c)
				s++;
			if (*s == c)
				s++;
		}
		if (*s == sep)
		{
			s++;
			++count_w;
		}
		while (*s && *s != sep && *s != '\'' && *s != '\"')
			s++;
	}
	return (++count_w);
}

void	loop_word_quote(int *len_w, char *s, char quote_tp)
{
	while (*s && *s != quote_tp)
	{
		s++;
		len_w++;
	}
}

char	**to_malloc(char *buff, char **tab, char c)
{
	if (!buff)
		return (NULL);
	tab = (char **)malloc((ft_count_word(buff, c, 0) + 1) * sizeof(char *));
	if (!(tab))
		return (NULL);
	return (tab);
}

char	*divide_loop(char *buff, int i, char **tab, int c)
{
	int		j;
	char	quote_tp;

	j = 0;
	tab[i] = (char *)malloc(sizeof(char) * (lenght_of_word(buff, c) + 1));
	if (!tab[i])
		return (0);
	while (*buff && *buff != c)
	{
		if (*buff && (*buff == '\"' || *buff == '\''))
		{
			quote_tp = *buff;
			tab[i][j++] = *buff++;
			while (*buff && *buff != quote_tp)
				tab[i][j++] = *buff++;
			tab[i][j++] = *buff++;
		}
		while (*buff && *buff != '\"' && *buff != '\'' && *buff != c)
			tab[i][j++] = *buff++;
	}
	tab[i][j] = '\0';
	return (buff);
}

char	**ft_split_pipe(char *buff, char c, int i)
{
	int		count_w;
	char	**tab;

	tab = to_malloc(buff, NULL, c);
	if (!tab)
		return (NULL);
	count_w = ft_count_word(buff, c, 0);
	while (i < count_w)
	{
		buff = divide_loop(buff, i, tab, c);
		i++;
		if (*buff == c)
			buff++;
	}
	tab[i] = 0;
	return (tab);
}
