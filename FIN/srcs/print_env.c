/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:53:52 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/30 14:58:04 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env_elem(t_envlist *list, char *tempoline, int l, int equal)
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

void	printlistenv(t_envlist *list)
{
	int			l;
	int			equal;
	char		*tempoline;

	if (!list)
		return ;
	while (list != NULL)
	{
		if (list->line)
		{
			l = ft_strlen(list->line);
			equal = searchequal(list->line) - 1;
			tempoline = ft_substr(list->line, 11, l - (l - equal) - 9);
			if (tempoline)
				print_env_elem(list, tempoline, l, equal);
		}
		list = list->next;
	}
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
