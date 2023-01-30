/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:35:20 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/28 22:47:10 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	whereend(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=' || line[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

t_envlist	*findline(t_envlist *envlist, char *line)
{
	int		i;
	int		lenline;

	if (line == NULL || envlist == NULL)
		return (NULL);
	lenline = ft_strlen(line);
	while (envlist != NULL && envlist->next != NULL)
	{
		i = 0;
		while (envlist->line[i + 11] && envlist->line[i + 11] == line[i + 1])
			i++;
		if (i == lenline - 1 && i == whereend(envlist->line) - 11)
			return (envlist);
		else
			envlist = envlist->next;
	}
	if (envlist)
	{
		i = 0;
		while (envlist->line[i + 11] && envlist->line[i + 11] == line[i + 1])
			i++;
		if (i == lenline - 1 && i == whereend(envlist->line) - 11)
			return (envlist);
	}
	return (NULL);
}

char	*cutline(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (line == NULL)
		return (NULL);
	while (line[i] && line[i] != '=')
		i++;
	str = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	return (str);
}

char	*get_env_line(t_envlist *envlist, char *line)
{
	t_envlist	*tempo;
	int			lenline;
	char		*lineresult;

	lineresult = NULL;
	lenline = ft_strlen(line);
	tempo = envlist;
	envlist = findline(envlist, line);
	if (envlist)
	{
		lineresult = cutline(envlist->line);
	}
	free(line);
	return (lineresult);
}

char	*removequote(char *line)
{
	char	*tempo;
	int		lenline;

	lenline = ft_strlen(line);
	tempo = line;
	if (lenline > 2)
	{
		line = ft_substr(line, 1, lenline - 2);
		free(tempo);
	}
	return (line);
}
