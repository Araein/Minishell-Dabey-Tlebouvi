/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:40:48 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 21:05:24 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	startchild(t_list *list, int **pipefd, char **env, int index)
{
	if (index == 0)
	{
		if (firstchild(list, pipefd, env) == -1)
			return (freeandclose(list, pipefd, list->command_count, 1));
		close(pipefd[0][1]);
		index++;
	}
	else if (index > 0 && index < list->command_count - 1)
	{
		if (middlechild(list, pipefd, env) == -1)
			return (freeandclose(list, pipefd, list->command_count, 1));
		close(pipefd[index][1]);
		index++;
	}
	else
	{
		if (lastchild(list, pipefd, env) == -1)
			return (freeandclose(list, pipefd, list->command_count, -1));
		freeandclose(list, pipefd, list->command_count, 1);
		index++;
	}
	return (0);
}

int	firstchild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;

	p_pid = fork();
	if (p_pid == 0)
	{
		if (!(list->clean_tab))
			return (-1);
		if (callredirec(list, pipefd, 1) == -1 || list->cmd[0] == NULL)
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			paths = getpath(list->cmd[0], getmyline(env));
			if (!paths)
			{
				write(2, list->cmd[0], ft_strlen(list->cmd[0]));
				write(2, ": command not found\n", 20);
				g_status = 127;
				return (-1);
			}
			execve(paths, list->cmd, env);
		}
		return (-1);
	}
	return (0);
}

int	middlechild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;

	p_pid = fork();
	if (p_pid == 0)
	{
		if (!(list->clean_tab))
			return (-1);
		if (callredirec(list, pipefd, 3) == -1 || list->cmd[0] == NULL)
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			paths = getpath(list->cmd[0], getmyline(env));
			if (!paths)
			{
				write(2, list->cmd[0], ft_strlen(list->cmd[0]));
				write(2, ": command not found\n", 20);
				g_status = 127;
				return (-1);
			}
			execve(paths, list->cmd, env);
		}
		return (-1);
	}
	return (0);
}

int	lastchild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;

	p_pid = fork();
	if (p_pid == 0)
	{
		if (!(list->clean_tab))
			return (-1);
		if (callredirec(list, pipefd, 2) == -1 || list->cmd[0] == NULL)
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			paths = getpath(list->cmd[0], getmyline(env));
			if (!paths)
			{
				write(2, list->cmd[0], ft_strlen(list->cmd[0]));
				write(2, ": command not found\n", 20);
				g_status = 127;
				return (-1);
			}
			execve(paths, list->cmd, env);
		}
		return (-1);
	}
	return (0);
}

int	command_countfunc(t_list *list)
{
	int		i;
	t_list	*tempo;
	int		command_count;

	i = 0;
	command_count = 0;
	tempo = list;
	while (list)
	{
		list->exit = 0;
		i = 0;
		while (list->cmd[i])
		{
			if (ft_strcmp(list->cmd[i], "<<") == 0)
				setup_in(list->redirfd, list->to_unlink, list->cmd[i + 1], 1);
			i++;
		}
		command_count++;
		list = list->next;
	}
	list = tempo;
	return (command_count);
}
