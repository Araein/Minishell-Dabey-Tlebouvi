/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:15:58 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/05 18:18:24 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// char	*ft_strdup(const char *str)
// {
// 	int		i;
// 	char	*dest;

// 	i = 0;
// 	dest = (char *)malloc(sizeof(char) * (ft_strlen((char *)str) + 1));
// 	if (!dest)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		dest[i] = str[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*answer;
// 	size_t	i;

// 	i = 0;
// 	if (!s || len <= 0 || start >= (unsigned int)ft_strlen(s))
// 		return (ft_strdup(""));
// 	answer = malloc(sizeof(char) * len + 1);
// 	if (!answer)
// 		return (NULL);
// 	while (s[start] && i < len)
// 	{
// 		answer[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	answer[i] = '\0';
// 	return (answer);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s != (char)c)
// 	{
// 		if (*s == '\0')
// 			return (NULL);
// 		s++;
// 	}
// 	return ((char *)s);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char			*new;
// 	int				i;
// 	int				j;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!new)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		new[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		new[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }
