/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_exec_need.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:27:27 by dabey             #+#    #+#             */
/*   Updated: 2023/01/28 22:46:42 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	onecommand(t_list *list, char **env)
{
	char	*paths;
	int		p_pid;

	if (checkerrorcmd(list) == -1)
		return (-1);
	if (exportunset(list) == -1)
		return (1);
	p_pid = fork();
	if (p_pid == 0)
	{
		if (callredirec(list, NULL, 4) == -1 || list->cmd[0] == NULL)
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			paths = getpath(list->cmd[0], getmyline(env));
			if (!paths)
				return (errorpathorwait(list, 1));
			execve(paths, list->cmd, env);
			free(paths);
		}
		return (-1);
	}
	return (errorpathorwait(list, 2));
}

int	**mallocandpipe(int command_count)
{
	int	i;
	int	**pipefd;

	i = 0;
	pipefd = (int **)malloc((command_count - 1) * sizeof(int *));
	i = 0;
	while (i < (command_count - 1))
	{
		pipefd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < command_count - 1)
	{
		if (pipe(pipefd[i]) == -1)
			perror ("Error");
		i++;
	}
	return (pipefd);
}

t_list	*transferlistdata(t_list *list, int index, int command_count)
{
	if (index < command_count)
	{
		list = list->next;
		list->index = index;
		list->command_count = command_count;
	}
	return (list);
}

void	waitfunc(int command_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < command_count)
	{
		waitpid (-1, &status, 0);
		g_status = status / 256;
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
