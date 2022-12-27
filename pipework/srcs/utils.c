/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:37:17 by dabey             #+#    #+#             */
/*   Updated: 2022/12/08 15:41:45 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_init(t_list *list)
{
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
	{
		perror("Malloc failure");
		return (0);
	}
	list->type = 0;
	list->buffer = NULL;
	list->cmd = NULL;
	list->buf_size = 2048;// a verifier la taille
	list->buffer = (char *)malloc(sizeof(char) * (list->buf_size));
	if (!list->buffer)
	{
		perror("Malloc failure");
		return (0);
	}
	return (list);
}

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }

// int	ft_isalpha(int c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	else
// 		return (0);
// }

// int	ft_isalnum(int c)
// {
// 	if (ft_isdigit(c) || ft_isalpha(c))
// 		return (1);
// 	else
// 		return (0);
// }

int	ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int	ft_len_w(char const *s, char c)
// {
// 	size_t len_w;

// 	len_w = 0;
// 	while (*s != c && *s != '\0')
// 	{
// 		len_w++;
// 		s++;
// 	}
// 	return (len_w);
// }

// int	ft_count_w(char const *s, char c)
// {
// 	size_t count_w;

// 	count_w = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s != '\0')
// 			count_w++;
// 		while (*s != c && *s != '\0')
// 			s++;
// 	}
// 	return (count_w);
// }

char	**ft_split(char *s, char c)
{
	size_t i;
	size_t j;
	size_t count_w;
	char **tab;

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
	return (tab);
}
