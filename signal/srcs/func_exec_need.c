/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_exec_need.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:27:27 by dabey             #+#    #+#             */
/*   Updated: 2023/02/10 20:14:06 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_elem(char *myenv, char *tempoline, int l, int equal)
{
	char	*tempo;
	tempo = myenv;
	myenv = tempoline;
//	free(tempoline);
	tempoline = ft_substr(tempo, equal + 3, l - (equal + 4));
//	free(tempo);	
	if (tempoline)
	{
		tempo = myenv;
		myenv = ft_strjoin(myenv, tempoline);
		free(tempoline);
		free(tempo);
	}
	return (myenv);
}

char	**cleanmyenv(char **myenv)
{
	int			l;
	int			equal;
	char		*tempoline;
	int			i;

	i = 0;

	while (myenv[i] != NULL)
	{
		if (myenv[i])
		{
			l = ft_strlen(myenv[i]);
			equal = searchequal(myenv[i]) - 1;
			tempoline = ft_substr(myenv[i], 11, l - (l - equal) - 9);
			if (tempoline)
				myenv[i] = clean_elem(myenv[i], tempoline, l, equal);
		}
		i++;
	}
	return (myenv);
}

char	**getmyenv(t_list *list)
{
	int			i;
	char		**tempo;
	t_envlist	*tempoenvlist;

	list->myenv = NULL;
	i = 0;
	tempoenvlist = list->envlist;
	while (list->envlist)
	{
		i++;
		list->envlist = list->envlist->next;
	}
	list->envlist = tempoenvlist;
	tempo = (char **)malloc(sizeof (char **) * (i + 1));//retour d'erreur
	i = 0;
	while (list->envlist)
	{
		tempo[i] = list->envlist->line;
		i++;
		list->envlist = list->envlist->next;
	}
	tempo[i] = NULL;
	return (cleanmyenv(tempo));
}
// void	handle_sigquit(int sig)
// {
// 	int	status;

// 	(void)sig;
// 	fprintf(stderr, "\npasse dans sigquit\n");
// 	status = 0;
// 	waitpid(-1, &status, 0);
// 	if (!status)
// 	{
// 		write(1, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else
// 		write(1, "\n", 1);
// 	g_status = 131;

// }

int	onecommand(t_list *list, char **env)
{
	char				*paths;
	char				**myenv;
	int					status;
	int					p_pid;

	(void)env;
	status = 0;
	if (list->clean_tab)
	{
		p_pid = checkerrorcmd(list);
		if (p_pid < 0)
			return (p_pid);
		if (exportunset(list) == -1)
			return (1);
	}
	p_pid = fork();
	if (p_pid == 0)
	{
		if (callredirec(list, NULL, 5) == -1)
			return (-1);
		if (!(list->cmd))
			return (-1);
		if (checkbuiltin(list) == 0)
		{
			myenv = getmyenv(list);
			paths = getpath(list->cmd[0], getmyline(myenv));
			if (!paths)
				return (errorpathorwait(list, 1, myenv, NULL));
			if ((list->isdir = opendir(paths)))
				return (errorpathorwait(list, 3, myenv, paths));
			execve(paths, list->cmd, myenv);
			free(paths);
			if (myenv)
				freetab(myenv);
		}
		// fprintf(stderr, "\ncoucou status = %d\n", status);
		return (-1);
	}
	return (errorpathorwait(list, 2, NULL, NULL));
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

void	waitfunc(int command_count, t_list *list)
{
	int	status;
	int	i;

	(void)list;
	i = 0;
	while (i < command_count)
	{
		waitpid (-1, &status, 0);
		
//		if (status != 130 && status != 131)
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
