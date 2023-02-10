/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:43:00 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/27 17:40:10 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	searchequal(char *line)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*addquote(char *line)
{
	char	*result;
	char	*tempo;
	char	*newline;
	int		equal;

	equal = 0;
	while (line[equal] && line[equal] != '=')
		equal++;
	tempo = ft_strndup(line, equal + 1);
	result = ft_strjoin(tempo, "\"");
	free(tempo);
	tempo = result;
	newline = cutline(line);
	if (newline == NULL)
		result = ft_strjoin(tempo, "\0");
	else
	{
		result = ft_strjoin(tempo, newline);
		free(newline);
	}
	free(tempo);
	tempo = result;
	result = ft_strjoin(tempo, "\"" );
	free(tempo);
	return (result);
}
