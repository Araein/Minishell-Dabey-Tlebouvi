/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:33:42 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/27 15:32:55 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirectthis(t_list *list)
{
	if (redirect(list, 0) == -1)
	{
		if (list->to_unlink)
			unlink(list->to_unlink);
		return (-1);
	}
	redirectdup(list);
	if (list->to_unlink)
		unlink(list->to_unlink);
	return (1);
}

int	writefunc(int fd[2], char *doc, int j, char content)
{
	if (j == ft_strlen(doc) && content == '\n')
		return (1);
	else
	{
		write(fd[0], doc, j);
		write(fd[0], &content, 1);
		return (0);
	}
}

void	readfunc(int *u, char *doc, int fd[2])
{
	char	content;
	int		j;

	j = 0;
	write (1, "> ", 2);
	content = 0;
	while (content != '\n')
	{
		read(0, &content, 1);
		if (j == 0 && content == doc[j])
		{
			while (content == doc[j] && content != '\n')
			{
				j++;
				read(0, &content, 1);
			}
			*u = writefunc(fd, doc, j, content);
		}
		else
			write(fd[0], &content, 1);
		j++;
	}
}

int	redirect(t_list *list, int i)
{
	while (list->cmd[i])
	{
		if (ft_strcmp(list->cmd[i], "<") == 0)
		{
			if (setup_in(list->redirfd, list->to_unlink,
					list->cmd[i + 1], 0) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], "<<") == 0)
		{
			if (setup_in(list->redirfd, list->to_unlink,
					list->cmd[i + 1], 2) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">>") == 0)
		{
			if (setup_out(list->redirfd, list->cmd[i + 1], 1) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">") == 0)
			if (setup_out(list->redirfd, list->cmd[i + 1], 0) == -1)
				return (-1);
		i++;
	}
	return (1);
}
