/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:38:05 by dabey             #+#    #+#             */
/*   Updated: 2022/11/05 14:38:51 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int	check_quote(char *buffer)
{
	int	i;
	int c;
	int	quate;
	int	dbl_quate;

	i = 0;
	c = 0;
	quate = 0;
	dbl_quate = 0;
	while (buffer[i])
	{
		while (buffer[i] && buffer[i] != '\'' && buffer[i] != '\"')
			i++;
		if (buffer[i] == '\'')
		{
			quate++;
			c = 1;
		}
		else if (buffer[i] == '\"')
		{
			dbl_quate++;
			c = 2;
		}
		i++;
	}
	if (quate % 2 == 0 && dbl_quate % 2 == 0)
		return (c);
	else
		return (0);
}

void	ft_split_quote(char *s, t_list *list)
{
	size_t	i;
	size_t	j;
	char	**tab;
	size_t	count_w;
	size_t	is_quote;

	i = 0;
	is_quote = 
	if (!s)
		return (NULL);
	// check_quote(buffer);
	count_w = ft_count_w(s, ' ');
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*s == ' ' || *s == ' |')
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w(s, ' ') + 1));
		if (!tab[i])
			return (0);
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
}

int	parse_quote(char *buffer, t_list *list)
{
	int	quate_type;

	quate_type = check_quote(buffer);
	if (quate_type != 0)
		// ft_split_quote(buffer, list);
	else
	{
		printf("error : quote not close\n");
		return (0);
	}
	return(1);
}
*/