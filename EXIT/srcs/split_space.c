/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:50:01 by dabey             #+#    #+#             */
/*   Updated: 2022/12/06 18:55:33 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len_word(char const *s, char c)
{
	int	len_w;

	len_w = 0;
	while (*s != c && *s != '\0')
	{
		len_w++;
		s++;
	}
	return (len_w);
	}

int	split2_word(char *s, char sep)
{
	char	quote_tp;
	int		count_w;
	int		text;

	(void)sep;
	count_w = 0;
	text = 0;
	while (*s)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
				s++;
			s++;
			count_w++;
		}
		while (*s >= 9 && *s <= 32)
			s++;
		while (*s >= 33 && *s <= 122 && *s != '\'' && *s != '\"')
		{
			text++;
			s++;
		}
		if (text)
		{
			text = 0;
			count_w++;
		}
	}
	return (count_w);
}

int	len_w_split2(char *s, char sep)
{
	char	quote_tp;
	int		len_w;
	int		once;

	once = 1;
	len_w = 0;
	while (*s && *s == ' ' && once)
		s++;
	once = 0;
	while (*s && *s != ' ')
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			len_w++;
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
			{
				s++;
				len_w++;
			}
			s++;
			len_w++;
		}
		while (*s && *s != sep && *s != '\'' && *s != '\"')
		{
			len_w++;
			s++;
		}
	}
	return (len_w);
}

char	**split2(char *s, char c)
{
	int		i;
	int		j;
	int		count_w;
	char	quote_tp;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	count_w = split2_word(s, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = len_w_split2(s, c);
		tab[i] = (char *)malloc(sizeof(char) * (j + 1));
		if (!tab[i])
			return (0);
		j = 0;
		while (*s && *s == ' ')
			s++;
		while (*s && *s != c)
		{
			if (*s && (*s == '\"' || *s == '\''))
			{
				quote_tp = *s;
				tab[i][j++] = *s++;
				while (*s && *s != quote_tp)
					tab[i][j++] = *s++;
				tab[i][j++] = *s++;
			}
			while (*s && *s != '\"' && *s != '\'' && *s != c)
				tab[i][j++] = *s++;
		}
		tab[i++][j] = '\0';
		if (*s == c)
			s++;
	}
	tab[i] = 0;
	return (tab);
}