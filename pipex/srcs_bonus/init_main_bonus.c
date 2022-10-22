/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:21:42 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/17 17:08:57 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	dupbonus(t_pipe *pipex, int pipefd[2], int pipeout[2], int type)
{
	if (type == 1)
	{
		close (pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		dup2(pipex->fd[0], 0);
		close(pipex->fd[0]);
	}
	if (type == 2)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		dup2(pipex->fd[1], 1);
		close(pipex->fd[1]);
	}
	if (type == 3)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipeout[0]);
		dup2(pipeout[1], 1);
		close(pipeout[1]);
	}
}

void	structinit(t_pipe *pipex, int argc, char **env, char **argv)
{
	pipex->env = NULL;
	pipex->argv = NULL;
	pipex->argc = argc;
	pipex->type = 0;
	pipex->env = env;
	pipex->argv = argv;
	pipex->index = 0;
	pipex->program = argc - 3;
	pipex->islink = 0;
	pipex->iserr = 0;
}

int	**mallocandpipe(int argc, t_pipe *pipex)
{
	int	i;
	int	**pipefd;

	i = 0;
	pipefd = (int **)malloc((argc - 4) * sizeof(int *));
	i = 0;
	while (i < (argc - 4))
	{
		pipefd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < pipex->program - 1)
	{
		if (pipe(pipefd[i]) == -1)
			perror ("Error");
		i++;
	}
	return (pipefd);
}

void	freeandclose(t_pipe *pipex, int **pipefd, int argc, int type)
{
	int	j;
	int	i;
if (type != -1)
{
		j = 0;
	while (j < pipex->program - 1)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
}
if(type != 2)
{
		i = 0;
	while (i < argc - 4)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
}
	closefd(0, 1, 2);
	
}

void	waitfonc(int pipefd[2], t_pipe *pipex, int type)
{
	int	i;

	i = 0;
	if (type == 1)
	{
		close (pipefd[0]);
		close (pipefd[1]);
		waitpid (-1, NULL, 0);
		waitpid (-1, NULL, 0);
	}
	if (type == 2)
	{
		while (i < pipex->program)
		{
			waitpid (-1, NULL, 0);
			i++;
		}
	}
}
