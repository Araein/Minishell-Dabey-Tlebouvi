/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:43:16 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/27 16:20:06 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envlist	*ft_new_envnode(char *line, int created)
{
	t_envlist	*new;

	if (line == NULL)
		return (NULL);
	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
		return (NULL);
	new->line = line;
	new->created = created;
	new->next = NULL;
	return (new);
}

t_envlist	*ft_add_env(t_envlist *list, char *line, int created)
{
	t_envlist	*head;
	t_envlist	*new;

	head = NULL;
	new = ft_new_envnode(line, created);
	if (new == NULL)
	{
		if (line)
			free(line);
		return (NULL);
	}
	if (!(list))
		list = new;
	else
	{
		head = list;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	return (list);
}

void	printlistenv(t_envlist *list)
{
	t_envlist	*tempo;
	int			l;
	char		*tempoline;
	int			equal;

	tempo = list;
	if (!list)
		return ;
	while (list != NULL && list->next != NULL)
	{
		if (list->line)
		{
			l = ft_strlen(list->line);
			equal = searchequal(list->line) - 1;
			tempoline = ft_substr(list->line, 11, l - (l - equal) - 9);
			if (tempoline)
			{
				printf("%s", tempoline);
				free(tempoline);
				tempoline = ft_substr(list->line, equal + 3, l - (equal + 4));
				if (tempoline)
				{
					printf("%s", tempoline);
					free(tempoline);
				}
				printf("\n");
			}
		}
		list = list->next;
	}
	if (list != NULL && list->line)
	{
		l = ft_strlen(list->line);
		equal = searchequal(list->line) - 1; //attention au -1 a test
		tempoline = ft_substr(list->line, 11, l - (l - equal) - 9);
		if (tempoline)
		{
			printf("%s", tempoline);
			free(tempoline);
			tempoline = ft_substr(list->line, equal + 3, l - (equal + 4));
			if (tempoline)
			{
				printf("%s", tempoline);
				free(tempoline);
			}
			printf("\n");
		}
	}
	list = tempo;
}

void	printlist(t_envlist *list, int type)
{
	t_envlist	*tempo;

	if (type == 0)
		printlistenv(list);
	else if (list)
	{
		tempo = list;
		while (list != NULL && list->next != NULL)
		{
			if (list->line)
				printf("%s\n", list->line);
			list = list->next;
		}
		if (list != NULL)
			printf("%s\n", list->line);
		list = tempo;
	}
}

void	change_env_shlvl(char **env, t_envlist *envlist)
{
	char	*string;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	string = "SHLVL=";
	result = NULL;
	while (env[i])
	{
		while (env[i][j])
		{
			if (env[i][j] == string[j])
				j++;
			else
				break;
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
	{
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
}

t_envlist	*change_shlvl(t_envlist *envlist, char **env)
{
	char		*line_value;
	char		*joinline;
	t_envlist	*tempo;
	char		**tempotab;
	int			value;

	change_env_shlvl(env, envlist);
	tempo = envlist;
	envlist = findline(envlist, "$SHLVL");
	if (envlist)
	{
		line_value = cutline(envlist->line);
		line_value = removequote(line_value);
		value = ft_atoi(line_value);
		free(line_value);
		value++;
		line_value = ft_itoa(value);
		joinline = ft_strjoin("export SHLVL=", line_value);
		free(line_value);
		envlist = tempo;
		tempotab = ft_split(joinline, ' ');
		envlist = built_in_export(envlist, tempotab);
		freetab(tempotab);
		free(joinline);
		return (envlist);
	}
	else
	{
		tempotab = ft_split("export SHLVL=1", ' ');
		tempo = built_in_export(tempo, tempotab);
		tempo->shlvl_line = NULL;
		freetab(tempotab);
	}
	return (tempo);
}

t_envlist	*make_env(char **env)
{
	int			i;
	char		*addquoteline;
	t_envlist	*envlist;

	i = 0;
	envlist = NULL;
	if (env[i] == NULL)
		return (NULL);
	while (env[i])
	{
		addquoteline = addquote(env[i]);
		envlist = ft_add_env(envlist,
				ft_strjoin("declare -x ", addquoteline), 1);
		free(addquoteline);
		i++;
	}
	envlist = change_shlvl(envlist, env);
	return (envlist);
}

void	free_list_env(t_envlist *list)
{
	t_envlist	*tmp;

	if (list)
	{
		while (list->next != NULL)
		{
			if (list->created == 1)
				free(list->line);
			tmp = list;
			list = list->next;
			free(tmp);
		}
		if (list->created == 1)
			free(list->line);
		free(list);
	}
}
