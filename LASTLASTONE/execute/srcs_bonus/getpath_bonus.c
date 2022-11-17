/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:16:36 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/17 18:29:57 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*getmyline(char **env)
{
	int		i;
	int		j;
	char	*goodline;

	j = 0;
	i = 0;
	goodline = "PATH=";
	while (env[i])
	{
		while (env[i][j] == goodline[j] && j < 5)
			j++;
		if (j == 5)
			return (env[i] + 5);
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}

char	*minifreetab(char **tab, char *result)
{
	freetab(tab);
	return (result);
}

int	checkpro(char *pro)
{
	int	i;

	i = 0;
	while (i < ft_strlen(pro))
	{
		if (pro[i] == '/')
			return (1);
		i++;
	}
	return (-1);
}

char	*getpath(char *pro, char *goodline, t_pipe *pipex)
{
	char	**paths;
	char	**tempo;
	char	*tmp;
	char	*result;

	if (checkpro(pro) == 1 && access(pro, F_OK) == 0)
	{
		pipex->islink = 1;
		return (pro);
	}
	if (goodline == NULL)
		return (NULL);
	paths = ft_split(goodline, ':');
	tempo = paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		result = ft_strjoin(tmp, pro);
		free(tmp);
		if (access(result, F_OK) == 0)
			return (minifreetab(tempo, result));
		free(result);
		paths++;
	}
	freetab(tempo);
	return (NULL);
}

int	patherror(char **pro, int fd, int pipefd1, int pipefd2)
{
	ft_putstr_fd("zsh: command not found: ", 2); //mettre message bash
	ft_putstr_fd(pro[0], 2);
	ft_putchar_fd('\n', 2);
	freetab(pro);
	closefd(fd, pipefd1, pipefd2);//, pipefd2);
	return (-1);
}
int	patherrormid(char **pro, int pipefd1, int pipefd2)//, int fd, int pipefd1, int pipefd2)
{
	ft_putstr_fd("zsh: command not found: ", 2); //mettre message bash
	ft_putstr_fd(pro[0], 2);
	ft_putchar_fd('\n', 2);
	freetab(pro);
	closefd(pipefd1, pipefd2, -1);
	return (-1);
}
