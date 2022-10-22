/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/10/21 20:45:23 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list_philo(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

t_list	*ft_new_philo(char *cmd_i)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->cmd = ft_split(cmd_i, ' ');
	new->next = NULL;
	// printf("ok_1\n");
	return (new);
}

t_list	*ft_add_node(t_list *list, char *cmd_i)
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	new = ft_new_philo(cmd_i);
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

int	main(void)
{
	int			j;
	int			i;
	t_list		*list;
	t_list		*tmp;
	char		*buffer;
	char		**str_cmd;

	buffer = NULL;
	list = NULL;
	str_cmd = NULL;
	// list = ft_init(list);
	while ((buffer = readline("Minishell$> ")) > 0)
	{
		i = 0;
		str_cmd = ft_split(buffer, '|');
		while(str_cmd[i] != 0)
		{
			list = ft_add_node(list, str_cmd[i]);
			i++;
		}
		free(buffer);
		tmp = list;
		while (tmp != 0)
		{
			j = 0;
			while (list->cmd[j] != 0)
			{
				printf("cmd = %s\n",list->cmd[j]);
				j++;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
//test     "coucou" bonjour "salut ca va?"    oui "super     moi | aussi"    "yes

	// list = ft_init(list);
	//if (strcmp(cmd[i], "exit") == 0)
	//	exit(0);