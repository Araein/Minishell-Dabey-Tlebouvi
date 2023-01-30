/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:50:41 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/30 16:20:32 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checkvariable(char *line)
{
	int	i;

	i = 0;
	if (line[i] != '_' && (line[i] < 65 || line[i] > 90)
		&& (line[i] < 97 || line[i] > 122))
		return (1);
	return (0);
}

t_envlist	*equalfound(t_envlist *envlist, char **variables, int i)
{
	char	**doubletempo;
	char	*tempo;
	char	*quoteline;
	int		j;

	j = 0;
	while (variables[i][j] && variables[i][j] != '=')
		j++;
	tempo = ft_substr(variables[i], 0, j);
	doubletempo = ft_split(tempo, ' ', 0, 0);
	envlist = unset_line(doubletempo, envlist, 0);
	free(tempo);
	freetab(doubletempo);
	j = 0;
	quoteline = addquote(variables[i]);
	tempo = ft_strjoin("declare -x ", quoteline);
	free(quoteline);
	envlist = ft_add_env(envlist, tempo, 1);
	g_status = 0;
	return (envlist);
}

t_envlist	*equalnotfound(t_envlist *envlist, char **variables, int i)
{
	char	*tempo;

	tempo = ft_strjoin("$", variables[i]);
	if (!(findline(envlist, tempo)))
	{
		if (tempo)
			free(tempo);
		tempo = ft_strjoin("declare -x ", variables[i]);
		envlist = ft_add_env(envlist, tempo, 1);
		g_status = 0;
	}
	else
		if (tempo)
			free(tempo);
	return (envlist);
}

void	error_export(char **var, int i)
{
	printf("bash: export: `%s': not a valid identifier\n", var[i]);
	g_status = 1;
}

t_envlist	*built_in_export(t_envlist *envlist, char **line)
{
	char		**var;
	int			i;

	i = 0;
	while (line[i])
		i++;
	if (i == 1 && ft_strcmp(line[0], "export") == 0)
		printlist(envlist, 1);
	else
	{
		i = 1;
		var = line;
		while (var[i])
		{
			if (checkvariable(var[i]) == 1)
				error_export(var, i);
			else if (searchequal(var[i]))
				envlist = equalfound(envlist, var, i);
			else
				envlist = equalnotfound(envlist, var, i);
			i++;
		}
	}
	return (envlist);
}
