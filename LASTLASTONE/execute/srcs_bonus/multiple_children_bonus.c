/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_children_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:13:04 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/26 21:14:53 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	startchildren(int pipefd[2], int type, char **argv, char **env)
{
	int		fd[2];

	if (type == 1)
	{
		if (firstherechild (pipefd, fd, argv, env) == -1)
			return (-1);
		if (secondherechild (pipefd, fd, argv, env) == -1)
			return (-1);
	}
	else
	{
		if (firstchild (pipefd, fd, argv, env) == -1)
			return (-1);
		if (secondchild (pipefd, fd, argv, env) == -1)
			return (-1);
	}
	return (0);
}

int	firstchild2(t_pipe *pipex, int pipefd[2])
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd));
	if (p_pid == 0)
	{
		pipex->fd[0] = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd[0] < 0)
			return (errorfd(pipefd, pipex, 1));
		pro = ft_split(pipex->argv[2], ' '); //secure
		paths = getpath(pro[0], getmyline(pipex->env), pipex);
		if (!paths)
			return (patherror(pro, pipex->fd[0], pipefd[0], pipefd[1]));
		dupbonus(pipex, pipefd, NULL, 1);
		execve(paths, pro, pipex->env);
		execerror(pro, paths, pipex);
	}
	pipex->index++;
	return (0);
}

int	middlechild(t_pipe *pipex, int pipefd[2], int pipeout[2])
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd));
	if (p_pid == 0)
	{
		pro = ft_split(pipex->argv[pipex->index + 2], ' '); //secure
		paths = getpath(pro[0], getmyline(pipex->env), pipex);
		if (!paths)
			return (patherrormid(pro, /*pipex->fd[0],*/ pipefd[0], pipefd[1]));
		dupbonus(pipex, pipefd, pipeout, 3);
		execve(paths, pro, pipex->env);
		execerror(pro, paths, pipex);
	}
	return (0);
}

int	secondchild2(t_pipe *pipex, int pipefd[2])
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;	

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd));
	if (p_pid == 0)
	{
		pipex->fd[1] = open(pipex->argv[pipex->argc - 1],
				O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (pipex->fd[1] < 0)
			return (errorfd(pipefd, pipex, 3));
		pro = ft_split(pipex->argv[pipex->argc - 2], ' '); //secure
		paths = getpath(pro[0], getmyline(pipex->env), pipex);
		if (!paths)
			return (patherror(pro, pipex->fd[1], pipefd[0], pipefd[1]));
		dupbonus(pipex, pipefd, NULL, 2);
		execve(paths, pro, pipex->env);
		execerror(pro, paths, pipex);
	}
	return (0);
}

int	startchildren2(t_pipe *pipex, int argc)
{
	int	**pipefd;
	int	i;

	pipefd = mallocandpipe(argc, pipex);
	i = 0;
	while (i < pipex->program)
	{
		if (pipex->index == 0)
		{
			if (firstchild2(pipex, pipefd[pipex->index]) == -1)
			{
				freeandclose(pipex, pipefd, argc, 1);
				return (-1);
			}
			close(pipefd[0][1]); //les deux pipefd encore ouverts sont suremet dans first
		}
		else if (pipex->index > 0 && pipex->index < pipex->program - 1)
		{
			if (middlechild(pipex, pipefd[pipex->index - 1], pipefd[pipex->index]) == -1)
			{
				freeandclose(pipex, pipefd, argc, 1);
				return (-1);
			}
			close(pipefd[pipex->index - 1][1]);
			close(pipefd[pipex->index - 1][0]);//pas faire quand ca foire (mettre dans middlechild?)
			//closefd(pipefd[pipex->index - 1][0], pipefd[pipex->index - 1][1], -1);//, pipefd[pipex->index][1]);
			pipex->index++; //verifier un retour -1?
		}
		else
		{
		//	close(pipefd[pipex->index - 2][0]);
			if (secondchild2(pipex, pipefd[pipex->index - 1]) == -1) //VERFIER UN RETOUR -1?
			{
			//	printf("COUCOU\n");
			//	pipex->iserr = -1; //useless?
			 	freeandclose(pipex, pipefd, argc, -1);
			 	return (-1);
			}
		//	closefd(pipefd[pipex->index - 1][0], pipefd[pipex->index - 1][1], -1);
			freeandclose(pipex, pipefd, argc, 1);
		}
		i++;
	}
	//	free(pipefd); 
			// toujours problemes de fd  et pb quand milieu existe pas ->tester avec des ./ etc...
	//freeandclose(pipex, pipefd, argc, pipex->iserr);
	return (0);
}

//lorsaue ????????????????  = fd ferme trop tot (ou deux fois)

