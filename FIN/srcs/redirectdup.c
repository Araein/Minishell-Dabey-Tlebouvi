/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:13:44 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/26 14:15:58 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirectdup(t_list *list)
{
	if (list->redirfd[0] > 0)
	{
		dup2(list->redirfd[0], STDIN);
		close(list->redirfd[0]);
	}
	if (list->redirfd[1] > 0)
	{
		dup2(list->redirfd[1], STDOUT);
		close(list->redirfd[1]);
	}
}

void	type1(t_list *list, int **pipefd, int type)
{
	close (pipefd[0][0]);
	if (list->redirfd[0] > 0)
	{
		dup2(list->redirfd[0], STDIN);
		close(list->redirfd[0]);
	}
	if (list->redirfd[1] > 0)
	{
		dup2(list->redirfd[1], STDOUT);
		close(list->redirfd[1]);
	}
	else
		dup2(pipefd[0][1], STDOUT);
	close(pipefd[0][1]);
	close_allpipe(list, pipefd, type);
}

void	type2(t_list *list, int **pipefd, int type)
{
	close(pipefd[list->command_count - 2][1]);
	if (list->redirfd[1] > 0)
	{
		dup2(list->redirfd[1], STDOUT);
		close(list->redirfd[1]);
	}
	if (list->redirfd[0] > 0)
	{
		dup2(list->redirfd[0], STDIN);
		close(list->redirfd[0]);
	}
	else
		dup2(pipefd[list->command_count - 2][0], STDIN);
	close(pipefd[list->command_count - 2][0]);
	close_allpipe(list, pipefd, type);
}

void	type3(t_list *list, int **pipefd, int type)
{
	close(pipefd[list->index - 1][1]);
	close(pipefd[list->index][0]);
	if (list->redirfd[0] > 0)
	{
		dup2(list->redirfd[0], STDIN);
		close(list->redirfd[0]);
	}
	else
		dup2(pipefd[list->index - 1][0], STDIN);
	close(pipefd[list->index - 1][0]);
	if (list->redirfd[1] > 0)
	{
		dup2(list->redirfd[1], STDOUT);
		close(list->redirfd[1]);
	}
	else
		dup2(pipefd[list->index][1], STDOUT);
	close(pipefd[list->index][1]);
	close_allpipe(list, pipefd, type);
}

void	dupbonus(t_list *list, int **pipefd, int type)
{
	if (type == 1)
	{
		type1(list, pipefd, type);
	}
	if (type == 2)
	{
		type2(list, pipefd, type);
	}
	if (type == 3)
	{
		type3(list, pipefd, type);
	}
}
