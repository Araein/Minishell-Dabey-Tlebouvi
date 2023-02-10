/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:20:36 by dabey             #+#    #+#             */
/*   Updated: 2023/02/10 20:00:35 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_first_check(t_list *list)
{
	g_status = 1;
	free_list(list);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (list != NULL)
	{
		if (list->redirfd[0] > 0)
			close(list->redirfd[0]);
		if (list->redirfd[1] > 0)
			close(list->redirfd[1]);
		tmp = list;
		list = list->next;
		if (tmp->cmd)
			freetab(tmp->cmd);
		if (tmp->clean_tab)
			freetab(tmp->clean_tab);
		free(tmp);
	}
}

t_list	*ft_new_node(char *cmd_i, char *buffer, t_envlist *first)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->buffer = buffer;
	new->cmd = split2(cmd_i, ' ', 0);
	new->envlist = first;
	new->clean_string = NULL;
	new->redirfd[0] = 0;
	new->redirfd[1] = 0;
	new->next = NULL;
	new->exphere = 0;
	new->command_count = 0;
	new->index = 0;
	new->clean_string = NULL;
	new->clean_tab = NULL;
	new->isdir = NULL;
	new->statushandle = 0;
	return (new);
}

t_list	*ft_add_node(t_list *list, char *cmd_i, char *buffer, t_envlist *env)
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	new = ft_new_node(cmd_i, buffer, env);
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
