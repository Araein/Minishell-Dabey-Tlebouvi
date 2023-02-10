/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_childs_need.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:49:04 by dabey             #+#    #+#             */
/*   Updated: 2023/02/10 15:24:10 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	freeandclose(t_list *list, int **pipefd, int command_count, int type)
{
	int	j;
	int	i;

	if (type != -1)
	{
		j = 0;
		while (j < command_count - 1)
		{
			close(pipefd[j][0]);
			close(pipefd[j][1]);
			j++;
		}
	}
	if (type != 2)
	{
		i = 0;
		while (i < command_count - 1)
		{
			free(pipefd[i]);
			i++;
		}
		free(pipefd);
	}
	(void)list;
	return (-1);
}

int	callredirec(t_list *list, int **pipefd, int type)
{
	int	error;

	error = 0;
	if (type == 4)
		list->exphere = 4;
	else
		list->exphere = 1;
	error = redirectthis(list);
	// fprintf(stderr, "\nerror = %d\n", error);
	list->exphere = 0;
	freetab(list->cmd);
	list->cmd = NULL;
	list->cmd = list->clean_tab;
	list->clean_tab = NULL;
	if (type != 4 && type != 5)
		dupbonus(list, pipefd, type);
	return (error);
}

char	*getpath(char *pro, char *goodline)
{
	char	**paths;
	char	**tempo;
	char	*tmp;
	char	*result;

	if (checkpro(pro) == 1 && access(pro, F_OK) == 0)
		return (ft_strdup(pro));
	if (goodline == NULL)
		return (NULL);
	paths = ft_split(goodline, ':', 0, 0);
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
