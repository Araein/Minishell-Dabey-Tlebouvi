/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:40:31 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/26 21:18:56 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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



void	close3(t_list *list, int **pipefd, int i)
{
	while (i < list->command_count - 1)
	{
		if (i != list->index - 1)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		i++;
	}
}

void	close_allpipe(t_list *list, int **pipefd, int type)
{
	int		i;

	i = 0;
	if (type == 1)
	{
		i = 1;
		while (i < (list->command_count - 1))
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (type == 2)
	{
		while (i < list->command_count - 2)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (type == 3)
		close3(list, pipefd, i);
}

int	callredirec(t_list *list, int **pipefd, int type)
{
	int	error;

	error = 0;
	error = redirectthis(list);
	freetab(list->cmd);
	list->cmd = NULL;
	list->cmd = list->clean_tab;
	list->clean_tab = NULL;
	if (type != 4)
		dupbonus(list, pipefd, type);
	return (error);
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
		if (checkbuiltin(list, env) == 0)
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
		if (checkbuiltin(list, env) == 0)
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
		if (checkbuiltin(list, env) == 0)
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
		i = 0;
		list->to_unlink = NULL;
		list->redirfd[0] = 0;
		list->redirfd[1] = 0;
		list->exit = 0;
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

int	startchild(t_list *list, int **pipefd, char **env, int index, int cc)
{
	if (index == 0)
	{
		if (firstchild(list, pipefd, env) == -1)
			return (freeandclose(list, pipefd, cc, 1));
		close(pipefd[0][1]);
		index++;
	}
	else if (index > 0 && index < cc - 1)
	{
		if (middlechild(list, pipefd, env) == -1)
			return (freeandclose(list, pipefd, cc, 1));
		close(pipefd[index][1]);
		index++;
	}
	else
	{
		if (lastchild(list, pipefd, env) == -1)
			return (freeandclose(list, pipefd, cc, -1));
		freeandclose(list, pipefd, cc, 1);
		index++;
	}
	return (0);
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

int	exportunset(t_list *list)
{
	if (ft_strcmp(list->clean_tab[0], "export") == 0)
	{
		redirectthis(list);
		freetab(list->cmd);
		list->cmd = list->clean_tab;
		list->clean_tab = NULL;
		list->envlist = built_in_export(list->envlist, list->cmd);
		close_here(list);
		return (-1);
	}
	if (ft_strcmp(list->clean_tab[0], "unset") == 0)
	{
		redirectthis(list);
		freetab(list->cmd);
		list->cmd = list->clean_tab;
		list->clean_tab = NULL;
		list->envlist = unset_line(list->cmd, list->envlist, 1);
		close_here(list);
		return (-1);
	}	
	return (1);
}

int	checkerrorcmd(t_list *list)
{
	if (!(list->clean_tab))
		return (-1);
	if (ft_strcmp(list->clean_tab[0], "exit") == 0)
	{
		redirectthis(list);
		freetab(list->cmd);
		list->cmd = list->clean_tab;
		list->clean_tab = NULL;
		built_in_exit(list);
		close_here(list);
		write(2, "exit\n", 5);
		return (-1);
	}	
	return (1);
}

int errorpathorwait(t_list *list, int type)
{
	int	status;

	if (type == 1)
	{
		write(2, list->cmd[0], ft_strlen(list->cmd[0]));
		write(2, ": command not found\n", 20);
		g_status = 127;
		return (-1);
	}
	else if (type == 2)
	{
		waitpid (-1, &status, 0);
		g_status = status / 256;
		return (1);
	}
	return (0);
}

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
		if (checkbuiltin(list, env) == 0)
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

int	exec(t_list *list, char **env)
{
	int		i;
	int		**pipefd;
	int		index;

	list->command_count = command_countfunc(list);
	if (list->command_count > 1)
	{
		index = 0;
		pipefd = mallocandpipe(list->command_count);
		i = 0;
		while (i < list->command_count)
		{
			if (startchild(list, pipefd, env, index, list->command_count) == -1)
				return (-1);
			index++;
			i++;
			list = transferlistdata(list, index, list->command_count);
		}
		waitfunc(list->command_count);
	}
	else if (onecommand(list, env) == -1)
		return (-1);
	close_here(list);
	return (1);
}

void close_here(t_list *tempo)
{
	int	i;

	while (tempo)
	{
		i = 0;
		while (tempo->cmd[i])
		{
			if (ft_strcmp(tempo->cmd[i], "<<") == 0)
				unlink(tempo->cmd[i + 1]);
			i++;
		}
		tempo = tempo->next;
	}
	return ;
}
