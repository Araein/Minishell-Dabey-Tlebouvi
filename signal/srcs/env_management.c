/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:43:16 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/08 15:03:19 by tlebouvi         ###   ########.fr       */
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
	new->shlvl_line = NULL;
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
	{
		list = new;
		list->shlvl_line = NULL;
	}
	else
	{
		head = list;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	return (list);
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
			{
				free(list->line);
				list->line = NULL;
			}
			tmp = list;
			list = list->next;
			free(tmp);
			tmp = NULL;
		}
		if (list->created == 1)
		{
			free(list->line);
			list->line = NULL;
		}
		if (list)
			free(list);
		list = NULL;
	}
}
