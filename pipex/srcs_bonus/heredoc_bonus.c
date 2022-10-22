/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:49:07 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/13 16:03:05 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	readfunc(int *u, char **argv, int fd[2])
{
	char	content;
	int		j;

	j = 0;
	write (1, "pipe heredoc> ", 14);
	content = 0;
	while (content != '\n')
	{
		read(0, &content, 1);
		if (j == 0 && content == argv[2][j])
		{
			while (content == argv[2][j] && content != '\n')
			{
				j++;
				read(0, &content, 1);
			}
			*u = writefunc(fd, argv[2], j, content);
		}
		else
			write(fd[0], &content, 1);
		j++;
	}
}

int	setuphere(char **argv, int fd[2])
{
	int		u;

	fd[0] = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0000664);
	if (fd[0] == -1)
		return (-1);
	u = 0;
	while (u == 0)
		readfunc(&u, argv, fd);
	close(fd[0]);
	return (0);
}

int	secondherechild(int pipefd[2], int fd[2], char **argv, char **env)
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd));
	if (p_pid == 0)
	{
		if (openfd(argv[5], fd, 3, pipefd) == 0)
			return (0);
		pro = ft_split(argv[4], ' ');
		paths = getpath(pro[0], getmyline(env), NULL);
		if (!paths)
			return (patherror(pro, fd[1], pipefd[0], pipefd[1]));
		dupfonc(pipefd, fd, 2);
		execve(paths, pro, env);
		perror("Error");
		freetab(pro);
		free(paths);
		closefd(0, 1, 2);
	}
	return (0);
}

void	dealwitherror(char **pro, char *paths)
{
	perror("Error");
	freetab(pro);
	free(paths);
	closefd(0, 1, 2);
}

int	firstherechild(int pipefd[2], int fd[2], char **argv, char **env)
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd));
	if (p_pid == 0)
	{
		if (setuphere(argv, fd) == -1 || openfd(argv[1], fd, 2, pipefd) == -1)
			return (-1);
		unlink("./here_doc");
		pro = ft_split(argv[3], ' ');
		paths = getpath(pro[0], getmyline(env), NULL);
		if (!paths)
			return (patherror(pro, fd[0], pipefd[0], pipefd[1]));
		dupfonc(pipefd, fd, 1);
		execve(paths, pro, env);
		dealwitherror(pro, paths);
		write(2, "stop", 4);
	}
	waitpid (-1, NULL, 0);
	return (0);
}
