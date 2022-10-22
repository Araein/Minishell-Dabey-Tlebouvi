/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:16:36 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/13 17:59:13 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	openfd(char	*argv, int fd[2], int type, int pipefd[2])
{
	if (type == 1)
	{
		fd[1] = open(argv, O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (fd[1] < 0)
		{
			perror(argv);
			if (fd[0] != -1)
				close(fd[0]);
			return (0);
		}
	}
	else
	{
		fd[0] = open(argv, O_RDONLY);
		if (fd[0] < 0)
		{
			perror(argv);
			close(pipefd[0]);
			close(pipefd[1]);
			return (-1);
		}
	}
	return (1);
}

int	errorpid(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	perror("Error");
	return (-1);
}

int	dupfonc(int pipefd[2], int fd[2], int type)
{
	if (type == 1)
	{
		close (pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
			return (-1);
		close (pipefd[1]);
		if (dup2(fd[0], 0) == -1)
			return (-1);
		close (fd[0]);
	}
	if (type == 2)
	{
		close (pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
			return (-1);
		close (pipefd[0]);
		if (dup2(fd[1], 1) == -1)
			return (-1);
		close (fd[1]);
	}
	return (0);
}

int	secondchild(int pipefd[2], int fd[2], char **argv, char **env)
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd));
	if (p_pid == 0)
	{
		if (openfd(argv[4], fd, 1, pipefd) == 0)
			return (0);
		pro = ft_split(argv[3], ' ');
		paths = getpath(pro[0], getmyline(env), NULL);
		if (!paths)
			return (patherror(pro, fd[1], pipefd[0], pipefd[1]));
		if (dupfonc(pipefd, fd, 2) == -1)
			return (-1);
		execve(paths, pro, env);
		perror("Error");
		if(pro[1])
			freetab(pro);
		else
			free(pro);
	//	free(paths);
		closefd(0, 1, 2);
	}
	return (0);
}

int	firstchild(int pipefd[2], int fd[2], char **argv, char **env)
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd));
	if (p_pid == 0)
	{
		if (openfd(argv[1], fd, 2, pipefd) == -1)
			return (-1);
		pro = ft_split(argv[2], ' ');
		paths = getpath(pro[0], getmyline(env), NULL);
		if (!paths)
			return (patherror(pro, fd[0], pipefd[0], pipefd[1]));
		if (dupfonc(pipefd, fd, 1) == -1)
			return (-1);
		execve(paths, pro, env);
		perror("Error");
		if(pro[1])
			freetab(pro);
		else
			free(pro);
	//	if(paths)
	//		free(paths);    //pro renvoit directement argv donc argv = pas malloc donc problemes
		closefd(0, 1, 2);
	}
	return (0);
}
