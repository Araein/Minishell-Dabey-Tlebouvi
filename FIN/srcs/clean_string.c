/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:51:10 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/30 16:53:53 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redi(char *line, int i)
{
	if (line[i] == '>')
	{
		if (line[++i] == '>')
			return (2);
		else
			return (1);
	}
	else if (line[i] == '<')
	{
		if (line[++i] == '<')
			return (2);
		else
			return (1);
	}
	return (0);
}

t_list	*to_split(t_list *head)
{
	head->clean_tab = ft_split(head->clean_string, ' ', 0, 0);
	if (head->clean_string)
		free(head->clean_string);
	head = head->next;
	return (head);
}

int	check_string(t_list *head, int i, int j)
{
	char	*tempo;
	char	*tempo2;

	tempo = NULL;
	tempo2 = NULL;
	while (head->cmd[i] && is_redi(head->cmd[i], j))
		i += 2;
	while (head->cmd[i])
	{	
		if (is_redi(head->cmd[i], j) == 0)
		{
			if (head->clean_string)
				tempo = ft_strjoin(head->clean_string, " ");
			head->clean_string = ft_strjoin(tempo, head->cmd[i]);
			if (tempo)
				free(tempo);
			if (tempo2)
				free(tempo2);
			tempo2 = head->clean_string;
		}
		else
			i++;
		i++;
	}
	return (i);
}

void	get_clean_string(t_list *list, int i, int j)
{
	int		redi_type;
	t_list	*head;

	head = list;
	redi_type = 0;
	if (!list)
		return ;
	while (head != 0)
	{
		i = 0;
		while (head->cmd[i])
		{		
			j = 0;
			i = check_string(head, i, j);
		}
		head = to_split(head);
	}
}
