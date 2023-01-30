/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:02:32 by dabey             #+#    #+#             */
/*   Updated: 2023/01/28 22:34:44 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec(t_list *list, char **env)
{
	int		i;
	int		**pipefd;
	int		index;

	list->command_count = command_countfunc(list);
	if (list->command_count > 1)
	{
		index = 0;
		pipefd = mallocandpipe(list->command_count);
		i = 0;
		while (i < list->command_count)
		{
			if (startchild(list, pipefd, env, index) == -1)
				return (-1);
			index++;
			i++;
			list = transferlistdata(list, index, list->command_count);
		}
		waitfunc(list->command_count);
	}
	else if (onecommand(list, env) == -1)
		return (-1);
	close_here(list);
	return (1);
}

void	close_here(t_list *tempo)
{
	(void)tempo;
	unlink("/tmp/here_doc");
	return ;
}

void	close_allpipe(t_list *list, int **pipefd, int type)
{
	int		i;

	i = 0;
	if (type == 1)
	{
		i = 1;
		while (i < (list->command_count - 1))
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (type == 2)
	{
		while (i < list->command_count - 2)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (type == 3)
		close3(list, pipefd, i);
}

int	closesaved(t_list *list, int savedout, int savedin, int type)
{
	if (type == 0)
	{
		close_here(list);
		dup2(savedout, 1);
		close (savedout);
		dup2(savedin, 0);
		close(savedin);
	}
	if (type == 1)
	{
		close (savedout);
		close(savedin);
	}
	return (-1);
}

void	close3(t_list *list, int **pipefd, int i)
{
	while (i < list->command_count - 1)
	{
		if (i != list->index - 1)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		i++;
	}
}
