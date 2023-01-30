/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_env_expand_dlr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:28:53 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 20:52:58 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envlist	*findline2(t_envlist *envlist, char *line)
{
	int	i;
	int	lenline;

	if (line == NULL || envlist == NULL)
		return (NULL);
	lenline = ft_strlen(line);
	while (envlist != NULL)
	{
		i = 0;
		while (envlist->line[i] && envlist->line[i + 11] == line[i])
			i++;
		if (i == lenline && i == whereend(envlist->line) - 11)
			return (envlist);
		else
			envlist = envlist->next;
	}
	return (NULL);
}

char	*get_env_line_dollar(t_envlist *envlist, char *str_d, int *len)
{
	char		*lineresult;

	lineresult = NULL;
	envlist = findline2(envlist, str_d + 1);
	if (envlist)
	{
		lineresult = cutline(envlist->line);
		lineresult = removequote(lineresult);
		*len = ft_strlen(lineresult);
		free(str_d);
		str_d = NULL;
	}	
	else
	{
		*len = 0;
		return (NULL);
	}
	return (lineresult);
}

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

char	*split2_word_quote(char *s, int *count_w)
{
	char	quote_tp;

	quote_tp = *s;
	s++;
	while (*s && *s != quote_tp)
		s++;
	s++;
	(*count_w)++;
	return (s);
}
