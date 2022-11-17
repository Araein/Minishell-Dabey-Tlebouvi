/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:02:29 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/26 21:11:01 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	writefunc(int fd[2], char *argv, int j, char content)
{
	if (j == ft_strlen(argv) && content == '\n')
		return (1);
	else
	{
		write(fd[0], argv, j);
		write(fd[0], &content, 1);
		return (0);
	}
}

int	errorpid(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	perror("Error");
	return (-1);
}

void	execerror(char **pro, char *paths, t_pipe *pipex)
{
	perror("Error");
	freetab(pro);
	if (pipex->islink == 0)
		free(paths);
	else
		pipex->islink = 0;
	closefd(0, 1, 2);
}

int	errorfd(int pipefd[2], t_pipe *pipex, int type)
{
	if (type == 1)
	{
		perror(pipex->argv[1]);
		closefd(pipefd[0], pipefd[1], -1);
		pipex->index++;
		return (-1);
	}
	if (type == 2)
	{
		perror(pipex->argv[pipex->argc - 1]);
	//	closefd(pipefd[0], pipefd[1], -1);
		if (pipex->fd[0] != -1)
			close(pipex->fd[0]);
		return (-1);
	}
	if (type == 3)
	{
		perror(pipex->argv[pipex->argc - 1]);
		closefd(pipefd[0], pipefd[1], -1);
		pipex->index++;
		return (-1);
	}
	return (0);
}
