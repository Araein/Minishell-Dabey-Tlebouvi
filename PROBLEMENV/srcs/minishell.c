/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/11/04 21:37:50 by tlebouvi         ###   ########.fr       */
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
	t_envlist	*envlist;///////////
	char		*buffer;
	char		**str_cmd;

	argc = 0;
	argv = NULL;
	buffer = NULL;
	list = NULL;
	str_cmd = NULL;
	envlist = NULL;//////////////
	using_history();
	envlist = make_env(env);///////////

	
	while ((buffer = readline("Minishell$> ")) > 0)
	{
		add_history(buffer);

		if(ft_strcmp(buffer, "env") == 0)
		{
			printlist(envlist);///////////
			//envlist = ft_add_env(envlist, "COUCOU");

		}
		if(buffer[0] == '!')
		{
			/*envlist = */built_in_export(envlist, buffer);//////////
			//printlist(envlist);
		}
		i = 0;
		str_cmd = ft_split(buffer, '|');
		while(str_cmd[i] != 0)
		{
			list = ft_add_node(list, str_cmd[i], buffer);
			i++;
		}
		// history_list();
		// while (tmp->cmd[j] != 0)
		// {
		// 	printf("hystory = %s\n",tmp->cmd[j]);
		// 	j++;
		// }
		free(buffer);
		tmp = list;
		while (tmp != 0)
		{
		//	printf("new\n");
			j = 0;
			while (tmp->cmd[j] != 0)
			{
		//		printf("cmd = %s\n",tmp->cmd[j]);
				j++;
			}
			tmp = tmp->next;
		}
		// free_list(list);
	}
	return (0);
}
