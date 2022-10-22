/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:16:39 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/12 20:42:55 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	int		fd[2];
	int		status;

	if (argc != 5)
		return (ft_putstr_fd("Error: Wrong number of arguments\n", 2));
	if (env[0] == NULL)
	{
		ft_putstr_fd("Error: The environment is not available\n", 2);
		return (-1);
	}
	if (pipe(pipefd) == -1)
	{
		perror ("Error");
		return (-1);
	}
	if (firstchild (pipefd, fd, argv, env) == -1)
		return (-1);
	if (secondchild (pipefd, fd, argv, env) == -1)
		return (-1);
	close (pipefd[0]);
	close (pipefd[1]);
	waitpid (-1, &status, 0);
	waitpid (-1, &status, 0);
	return (0);
}
