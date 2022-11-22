/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:01:32 by dabey             #+#    #+#             */
/*   Updated: 2022/11/18 23:13:55 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int	ft_len_w_simple(char const *s, char c)
{
	int		len_w;
	char	quote_tp;

	len_w = 0;
	// int i = 0;
	while (*s && *s != c) // c = |
	{
		// while (*s && *s == ' ')
		// 	s++;
		if (*s && (*s == '\"' || *s == '\''))
		{
			// len_w++;// celui de la " || '
			quote_tp = *s;
			while (*s && *s != quote_tp)
			{
				s++;
				len_w++;
				// printf("i_quote = %d\n", ++i);
			}
			s++;
			// len_w++;
		}
		else if (*s && *s != c)
		{
			while (*s && *s != '\'' && *s != '\"' && *s != ' ')
			{
				len_w++;
				// printf("i_text = %d\n", ++i);
				s++;
			}
		}	
	}
	// printf("@ len_word = %d et s = %s@\n", len_w, s);
	return (len_w);
}

int	ft_count_w_simple(char const *s, char c)
{
	int	quote_tp;
	int	count_w;

	quote_tp = 0;
	count_w = 0;
	while (*s)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			quote_tp = *s;
			while (*s && *s != quote_tp)
				s++;
			s++;
		}
		if (*s == c)
		{
			s++;
			count_w++;
			while (*s && *s == c)
				s++;
		}
		else
			s++;
	}
	// printf("@ simple_word = %d et s = %s@\n", count_w + 1, s);
	return (++count_w);
}

char	**ft_split_space(char *s, char c)
{
	int		i;
	int		j;
	int		count_w;
	int		quote_tp;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	count_w = ft_count_w_simple(s, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*s && *s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w_simple(s, c) + 1));
		if (!tab[i])
			return (0);
		while (*s != c && *s != '\0')
		{
			if (*s && (*s == '\"' || *s == '\''))
			{
				quote_tp = *s;
				while (*s && *s != quote_tp)
					tab[i][j++] = *s++;
				s++;
			}
			if (*s && *s == ' ' && *(s - 1) == ' ')
			{
				s++;
				tab[i][j++] = *s++;
				while (*s && *s == ' ')
					s++;
			}
			else
				tab[i][j++] = *s++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
*/