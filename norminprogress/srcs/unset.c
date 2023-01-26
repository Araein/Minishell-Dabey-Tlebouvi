/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:28:58 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/26 14:30:39 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_2strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *str, int tsearched)
{
	int		i;
	char	searched;

	searched = (char)tsearched;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[ft_strlen(str) - i] == searched)
			return ((char *)&str[ft_strlen(str) - i]);
		i++;
	}
	if (str[ft_strlen(str) - i] == searched)
		return ((char *)&str[ft_strlen(str) - i]);
	return (0);
}

void	unset_line2(t_envlist *envlist, t_envlist *goodlist, t_envlist *first)
{
	t_envlist	*tempolist;

	if (envlist == goodlist)
	{
		tempolist = envlist;
		if (envlist->created == 1)
			free(envlist->line);
		envlist = envlist->next;
		free(tempolist);
		first = envlist;
	}
	else
	{
		while (envlist->next && envlist->next != goodlist)
			envlist = envlist->next;
		if (envlist->next == goodlist)
		{
			tempolist = envlist->next;
			if (envlist->next->created == 1)
				free(envlist->next->line);
			envlist->next = envlist->next->next;
			free(tempolist);
		}
	}
}

t_envlist	*unset_line(char **buffer, t_envlist *envlist, int type)
{
	char		*tempo;
	int			i;
	char		**args;
	t_envlist	*goodlist;
	t_envlist	*firstlist;

	i = type;
	args = buffer;
	firstlist = envlist;
	while (args[i])
	{
		tempo = ft_strjoin ("$", args[i]);
		goodlist = findline(envlist, tempo);
		free(tempo);
		if (goodlist)
		{
			unset_line2(envlist, goodlist, firstlist);
			envlist = firstlist;
		}
		i++;
	}
	return (firstlist);
}
