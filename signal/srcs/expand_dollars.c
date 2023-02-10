/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:04:18 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 20:51:49 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*free_expand(char *str_d, char *line, int *i, int k)
{
	*i += k;
	free(line);
	line = str_d;
	return (line);
}

char	*expand_truc(char *line, t_envlist *envlist, int *i, int k)
{
	int		j;
	char	*str_d;

	j = 0;
	expand_quote(line, i);
	if (line[*i] == '$' && line[*i + 1] != ' ' && line[*i + 1] != '$'
		&& line[*i + 1] != '\0')
	{
		if (line[*i + 1] == '?')
			str_d = funct_dollar_intero(NULL, i, &j, &k);
		else
		{
			j = *i + 1;
			while (line[j] && line[j] != ' ' && line[j] != '\''
				&& line[j] != '$' && line[j] != '\"')
				j++;
			str_d = ft_substr(line, *i, j - *i);
			str_d = get_env_line_dollar(envlist, str_d, &k);
		}
		str_d = ft_new_cmd(line, str_d, j - *i, *i);
		line = free_expand(str_d, line, i, k);
	}
	else if (line[*i])
		(*i)++;
	return (line);
}

char	*find_expand_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\0')
		line = expand_truc(line, envlist, &i, k);
	return (line);
}

char	**expand_dollar(t_envlist *envlist, char **str_cmd)
{
	int		i;

	if (!str_cmd)
		return (NULL);
	i = 0;
	while (str_cmd[i])
	{
		str_cmd[i] = find_expand_dollar(envlist, str_cmd[i]);
		i++;
	}
	return (str_cmd);
}
