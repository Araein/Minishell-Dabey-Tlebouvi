/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/11/09 19:30:03 by tlebouvi         ###   ########.fr       */
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
	t_envlist	*envlist;///////////
	char		*buffer;
	char		**str_cmd;
	t_envlist	*tempo;
//	int			i;

	argc = 0;
	argv = NULL;
	buffer = NULL;
	list = NULL;
	str_cmd = NULL;
	envlist = NULL;//////////////
	using_history();
	envlist = make_env(env);
//	i = 0;
	while ((buffer = readline("Minishell$> ")) > 0 && ft_strcmp(buffer, "exit") != 0)
	{
		add_history(buffer);
	//	printf("buffer = %s\n", buffer);
		if(buffer[0] == '$')
		{
			tempo = NULL;
			tempo = get_env_line(envlist, buffer);		//free tempo?
		}
		
		if(ft_strcmp(buffer, "env") == 0)
		{
			printlist(envlist);///////////
			//envlist = ft_add_env(envlist, "COUCOU");
		}
		if(buffer[0] == 'u' && buffer[1] == 'n' && buffer[2] == 's' && buffer[3] == 'e' && buffer[4] == 't')
		{
			envlist = unset_line(buffer, envlist);
			//envlist = ft_add_env(envlist, "COUCOU");
  
		}
		if(buffer[0] == '!')
		{
			/*envlist = */built_in_export(envlist, buffer);//////////
			//printlist(envlist);
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
		//	printf("new\n");
			j = 0;
			while (tmp->cmd[j] != 0)
			{
		//		printf("cmd = %s\n",tmp->cmd[j]);
				j++;
			}
			tmp = tmp->next;
		}
	}
	printf("exit : Good bye\n");
	free_list(list);
	return (0);
}
