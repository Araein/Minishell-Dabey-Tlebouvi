/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/11/17 14:42:16 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	free(tmp->buffer);
	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		freetab(tmp->cmd);
		free(tmp);
		// tmp = list;
	}
}

t_list	*ft_new_node(char *cmd_i, char *buffer)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->buffer = buffer;
	new->cmd = ft_split(cmd_i, ' ');
	new->next = NULL;
	return (new);
}

t_list	*ft_add_node(t_list *list, char *cmd_i, char *buffer)
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	new = ft_new_node(cmd_i, buffer);
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

int	main( int argc, char **argv, char **env)
{
	int			j;
	int			i;
	t_list		*list;
	t_list		*tmp;
	char		*buffer;
	char		**str_cmd;
	t_envlist	*tempo;
	t_envlist	*exportlist;
	t_envlist	*envlist;

	argc = 0;
	argv = NULL;
	buffer = NULL;
	list = NULL;
	str_cmd = NULL;
	exportlist = NULL;
	envlist = NULL;
	using_history();
	envlist = make_env(env, 0);
	exportlist = make_env(env, 1);
	while ((buffer = readline("Minishell$> ")) > 0 && ft_strcmp(buffer, "exit") != 0)
	{
		add_history(buffer);
		if(buffer[0] == '$')
		{
			tempo = NULL;
			tempo = get_env_line(envlist, buffer);		//free tempo?
		}
		
		if(ft_strcmp(buffer, "env") == 0)
			printlist(envlist);

		if(buffer[0] == 'u' && buffer[1] == 'n' && buffer[2] == 's' && buffer[3] == 'e' &&
		buffer[4] == 't' && buffer[5] == ' ')
		{
			envlist = unset_line(ft_substr(buffer, 6, ft_strlen(buffer) - 5), envlist, 0);
			exportlist = unset_line(ft_substr(buffer, 6, ft_strlen(buffer) - 5), exportlist, 1);
		}
		if(buffer[0] == 'e' && buffer[1] == 'x' && buffer[2] == 'p' && buffer[3] == 'o' &&
		 buffer[4] == 'r' && buffer[5] == 't' && (buffer[6] == ' ' || ft_strlen(buffer) == 6))
		{
			envlist = built_in_export(envlist, buffer, 0);
			exportlist = built_in_export(exportlist, buffer, 1);
		}
		i = 0;
		// parse_quote(buffer, list);
		str_cmd = ft_split(buffer, '|');
		while(str_cmd[i] != 0)
		{
			list = ft_add_node(list, str_cmd[i], buffer);
			i++;
		}
		free(buffer);
		tmp = list;
		while (tmp != 0)
		{
			j = 0;
			while (tmp->cmd[j] != 0)
				j++;
			tmp = tmp->next;
		}
	}
	free_list_env(envlist);
	free_list_env(exportlist);    //attention invalid free qqpart
	printf("exit : Good bye\n");
	free_list(list);
	return (0);
}
