/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:51:59 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/30 16:21:37 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_result(char *result, int i, char **env, t_envlist *envlist)
{
	char	*string;
	int		j;

	string = cutline(result);
	j = ft_atoi(string);
	free(string);
	j++;
	string = ft_itoa(j);
	result = ft_strjoin("SHLVL=", string);
	free(string);
	env[i] = result;
	envlist->shlvl_line = env[i];
}

void	change_env_shlvl(char **env, t_envlist *envlist, int i, int j)
{
	char	*string;
	char	*result;

	string = "SHLVL=";
	result = NULL;
	while (env[i])
	{
		while (env[i][j])
		{
			if (env[i][j] == string[j])
				j++;
			else
				break ;
		}
		if (j == 6)
		{
			result = env[i];
			break ;
		}
		j = 0;
		i++;
	}
	envlist->shlvl_line = NULL;
	if (result)
		get_result(result, i, env, envlist);
}

t_envlist	*do_shlvl(t_envlist *envlist, t_envlist *tempo, char **tempotab)
{
	char		*joinline;
	char		*line_value;
	int			value;

	line_value = cutline(envlist->line);
	line_value = removequote(line_value);
	value = ft_atoi(line_value);
	free(line_value);
	value++;
	line_value = ft_itoa(value);
	joinline = ft_strjoin("export SHLVL=", line_value);
	free(line_value);
	envlist = tempo;
	tempotab = ft_split(joinline, ' ', 0, 0);
	envlist = built_in_export(envlist, tempotab);
	freetab(tempotab);
	free(joinline);
	return (envlist);
}

t_envlist	*change_shlvl(t_envlist *envlist, char **env)
{
	t_envlist	*tempo;
	char		**tempotab;

	change_env_shlvl(env, envlist, 0, 0);
	tempo = envlist;
	envlist = findline(envlist, "$SHLVL");
	if (envlist)
		return (do_shlvl(envlist, tempo, NULL));
	else
	{
		tempotab = ft_split("export SHLVL=1", ' ', 0, 0);
		tempo = built_in_export(tempo, tempotab);
		tempo->shlvl_line = NULL;
		freetab(tempotab);
	}
	return (tempo);
}
