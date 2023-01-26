/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:33:42 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/25 22:00:26 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirectthis(t_list *list)
{
	if (redirect(list) == -1)
	{
		if (list->to_unlink)
			unlink(list->to_unlink);		
		return (-1);
	}
	redirectdup(list);
	if (list->to_unlink)
		unlink(list->to_unlink);
	return (1);
}

int	writefunc(int fd[2], char *doc, int j, char content)
{
	if (j == ft_strlen(doc) && content == '\n')
		return (1);
	else
	{
		write(fd[0], doc, j);
		write(fd[0], &content, 1);
		return (0);
	}
}

void	readfunc(int *u, char *doc, int fd[2])
{
	char	content;
	int		j;

	j = 0;
	write (1, "> ", 2);
	content = 0;
	while (content != '\n')
	{
		read(0, &content, 1);
		if (j == 0 && content == doc[j])
		{
			while (content == doc[j] && content != '\n')
			{
				j++;
				read(0, &content, 1);
			}
			*u = writefunc(fd, doc, j, content);
		}
		else
			write(fd[0], &content, 1);
		j++;
	}
}

int	setup_here(char *doc, char *to_unlink, int fd[2])
{
	int		u;

	if (to_unlink)
		unlink(to_unlink);
	if (fd[0] > 0)
		close(fd[0]);
	fd[0] = open(doc, O_CREAT | O_WRONLY | O_TRUNC, 0000664);
	if (fd[0] == -1)
	{
		perror(doc);
		g_status = 1;
		return (-1);
	}
	u = 0;
	while (u == 0)
		readfunc(&u, doc, fd);
	close(fd[0]);
	return (1);
}

int	setup_out(int fd[2], char *doc, int type)
{
	int i;

	i = 0; 
	if (type == 0)
	{
		fd[1] = open(doc, O_TRUNC | O_CREAT | O_RDWR, 0000664);
		if (fd[1] < 0)
		{
			perror(doc);
			g_status = 1;
			return (-1);
		}
	}
	else if (type == 1)
	{
		fd[1] = open(doc, O_APPEND | O_CREAT | O_RDWR, 0000664);
		if (fd[1] < 0)
		{
			perror(doc);
			g_status = 1;
			return (-1);
		}
	}
	return (1);
}

int setup_in(int fd[2], char *to_unlink, char *doc, int type)
{
	if (type == 1)
		setup_here(doc, to_unlink, fd);//faire gaffe retour	
	if (fd[0] > 0)
	 	close(fd[0]);
	fd[0] = open(doc, O_RDONLY);
	if (fd[0] < 0)
	{
		perror(doc);
		g_status = 1;
		return (-1);
	}
	return (1);
}

int	redirect(t_list *list)
{
	int	i;


	i = 0;
	list->redirfd[0] = 0;
	list->redirfd[1] = 0;
	list->to_unlink = NULL;
	while (list->cmd[i])
	{
		if (ft_strcmp(list->cmd[i], "<") == 0 || ft_strcmp(list->cmd[i], "<<") == 0)
		{
			if(setup_in(list->redirfd, list->to_unlink, list->cmd[i + 1], 0) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">>") == 0)
		{
			if (setup_out(list->redirfd, list->cmd[i + 1], 1) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">") == 0)
		{
//			fprintf(stderr, "\npassage %d / doc = %s\n", i, list->cmd[i + 1]);
			if (setup_out(list->redirfd, list->cmd[i + 1], 0) == -1)
				return (-1);
		}
		i++;
	}//check en cas de retour d'erreur d'une des fonctions
	return (1);
}

void	redirectdup(t_list *list)
{
	if (list->redirfd[0] > 0)
	{
		dup2(list->redirfd[0], STDIN);
		close(list->redirfd[0]);
	}
	if (list->redirfd[1] > 0)
	{
		dup2(list->redirfd[1], STDOUT);
		close(list->redirfd[1]);
	}
}

void	dupbonus(t_list *list, int **pipefd, int type)
{
	if (type == 1)
	{
		close (pipefd[0][0]);
		if (list->redirfd[0] > 0)
		{
			dup2(list->redirfd[0], STDIN);
			close(list->redirfd[0]);
		}
		if (list->redirfd[1] > 0)
		{
			dup2(list->redirfd[1], STDOUT);
			close(list->redirfd[1]);
		}
		else
			dup2(pipefd[0][1], STDOUT);
		close(pipefd[0][1]);
		close_allpipe(list, pipefd, type);
	}
	if (type == 2)
	{
		close(pipefd[list->command_count - 2][1]);
		if (list->redirfd[1] > 0)
		{
			dup2(list->redirfd[1], STDOUT);
			close(list->redirfd[1]);
		}
		if (list->redirfd[0] > 0)
		{
			dup2(list->redirfd[0], STDIN);
			close(list->redirfd[0]);
		}
		else
			dup2(pipefd[list->command_count - 2][0], STDIN);
		close(pipefd[list->command_count - 2][0]);
		close_allpipe(list, pipefd, type);
	}
	if (type == 3)
	{
		close(pipefd[list->index - 1][1]);
		close(pipefd[list->index][0]);
		if (list->redirfd[0] > 0)
		{
			dup2(list->redirfd[0], STDIN);
			close(list->redirfd[0]);
		}
		else
			dup2(pipefd[list->index - 1][0], STDIN);
		close(pipefd[list->index - 1][0]);
		if (list->redirfd[1] > 0)
		{
			dup2(list->redirfd[1], STDOUT);
			close(list->redirfd[1]);
		}
		else
			dup2(pipefd[list->index][1], STDOUT);
		close(pipefd[list->index][1]);
		close_allpipe(list, pipefd, type);
	}
}
