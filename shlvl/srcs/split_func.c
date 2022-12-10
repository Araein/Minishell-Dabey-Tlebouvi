/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:50:01 by dabey             #+#    #+#             */
/*   Updated: 2022/11/18 23:21:21 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_len_w(char const *s, char c)
{
       int len_w;

        len_w = 0;
        while (*s != c && *s != '\0')
        {
                len_w++;
                s++;
        }
        return (len_w);
}

int ft_count_w(char const *s, char c)
{
	int	count_w;
	int	quote;

	quote = 0;
	count_w = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			c = *s;
			++quote;
			s++;
			while (*s && *s != c)
				s++;
			if (*s == c)
			{
				--quote;
				s++;
			}
		
		}
		while (*s == c)
			s++;
		if (*s != '\0')
			count_w++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (count_w);
}

char	**ft_split_quote(char *buffer, char c)
{
	int		i;
	int		j;
	char	**tab;
	int		count_w;
	// size_t	is_quote;

	i = 0;
	if (!buffer)
		return (0);
	count_w = ft_count_w(buffer, '|');
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*buffer == ' ' || *buffer == c)
			buffer++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w(buffer, ' ') + 1));
		if (!tab[i])
			return (0);
		while (*buffer != c && *buffer != '\0')
		{
			while (*buffer && *buffer == ' ' && *(buffer - 1) == ' ')
				buffer++;
			tab[i][j++] = *buffer++;
			while (*buffer && *buffer == ' ' && *(buffer- 1) == ' ')
				buffer++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}

/*
int ft_len_w(char const *s, char c)
{
	int len_w;
	char quote_tp;

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
			if (*s == ' ')
			{
				if (*(s + 1) && *(s + 1) != '|')
				{
					s++;
					len_w++;
					// printf("i_space = %d\n", ++i);
				}
				while (*s && *s == ' ')
					s++;
			}
			while (*s && *s != '\'' && *s != '\"' && *s != c && *s != ' ')
			{
				len_w++;
				// printf("i_text = %d\n", ++i);
				s++;
			}
		}	
	}
	// printf("$ len_word = %d et s = %s$\n", len_w, s);
	return (len_w);
}

int ft_count_w(char const *s, char c)
{
	int	quote;
	int	booll;
	int	count_w;

	booll = 0;
	quote = 0;
	count_w = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s == c)
		{
			s++;
			count_w++;;
		}
		else if (*s == '\"')
		{
			s++;
			while (*s && *s != '\"')// erreur probable
				s++;
		}
		else if (*s && *s == '\'')//else
		{
			s++;
			while (*s && *s != '\'')
				s++;
			if (*s && *s == '\'')
				s++;
		}
		s++;
	}
	return (++count_w);
}

char	**ft_split_quote(char *buffer, char c)
{
	int		i;
	int		j;
	char	**tab;
	int		count_w;
	// size_t	is_quote;

	i = 0;
	if (!buffer)
		return (0);
	count_w = ft_count_w(buffer, '|');
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*buffer == ' ' || *buffer == c)
			buffer++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w(buffer, '|') + 1));
		if (!tab[i])
			return (0);
		while (*buffer != c && *buffer != '\0')
		{
			while (*buffer && *buffer == ' ' && *(buffer - 1) == ' ')
				buffer++;
			tab[i][j++] = *buffer++;
			while (*buffer && *buffer == ' ' && *(buffer- 1) == ' ')
				buffer++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
*/