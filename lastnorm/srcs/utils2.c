/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:22:49 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/26 14:16:52 by tlebouvi         ###   ########.fr       */
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
	list->buf_size = 2048;
	list->buffer = (char *)malloc(sizeof(char) * (list->buf_size));
	if (!list->buffer)
	{
		perror("Malloc failure");
		return (0);
	}
	return (list);
}

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	size_t	j;
	size_t	p;

	p = ft_strlen(s2);
	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * ((ft_strlen(s1) + p + 1)));
	if (!dest)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < p)
	{
		dest[i] = s2[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
