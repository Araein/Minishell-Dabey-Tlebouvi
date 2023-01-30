/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:50:01 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 20:49:06 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	split2_word(char *s)
{
	int		count_w;
	int		text;

	count_w = 0;
	text = 0;
	while (*s)
	{
		if (*s && (*s == '\"' || *s == '\''))
			s = split2_word_quote(s, &count_w);
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

char	*len_w_quote(char *s, int *len_w)
{
	char	quote_tp;	

	(*len_w)++;
	quote_tp = *s;
	s++;
	while (*s && *s != quote_tp)
	{
		s++;
		(*len_w)++;
	}
	s++;
	(*len_w)++;
	return (s);
}

int	len_w_split2(char *s, char sep)
{
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
			s = len_w_quote(s, &len_w);
		while (*s && *s != sep && *s != '\'' && *s != '\"')
		{
			len_w++;
			s++;
		}
	}
	return (len_w);
}

char	*do_split2(char **tab, int *i, int j, char *s)
{
	char	quote_tp;

	tab[*i] = (char *)malloc(sizeof(char) * (len_w_split2(s, ' ') + 1));
	if (!tab[*i])
		return (0);
	while (*s && *s == ' ')
		s++;
	while (*s && *s != ' ')
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			quote_tp = *s;
			tab[*i][j++] = *s++;
			while (*s && *s != quote_tp)
				tab[*i][j++] = *s++;
			tab[*i][j++] = *s++;
		}
		while (*s && *s != '\"' && *s != '\'' && *s != ' ')
			tab[*i][j++] = *s++;
	}
	tab[(*i)++][j] = '\0';
	if (*s == ' ')
		s++;
	return (s);
}

char	**split2(char *s, char c, int i)
{
	int		count_w;
	char	**tab;

	(void)c;
	if (!s)
		return (NULL);
	count_w = split2_word(s);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		s = do_split2(tab, &i, 0, s);
	}
	tab[i] = 0;
	return (tab);
}
