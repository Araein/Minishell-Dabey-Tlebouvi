/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:33:42 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/10 18:00:10 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirectthis(t_list *list)
{
	if (redirect(list, 0) == -1)
	{
		// fprintf(stderr, "\nerrorredirecthis = -1\n");
		return (-1);
	}
	redirectdup(list);
	return (1);
}

int	writefunc(int fd[2], char *doc, int j, char content)
{
	if (j == ft_strlen(doc) && content == '\n')
		return (1);
	else
	{
		(void)fd;
		write(fd[0], doc, j);
		write(fd[0], &content, 1);
		return (0);
	}
}

void	readfunc(int *u, char *doc, int fd[2])
{
	char	content;
	int		j;
	struct sigaction	sb;	

	sb.sa_handler = SIG_IGN;
	sigemptyset(&sb.sa_mask);
	sigaddset(&sb.sa_mask, SIGQUIT);
	sb.sa_flags = 0;
	if (sigaction(SIGQUIT, &sb, NULL) == -1)
		return ;
	j = 0;
	if (g_status == 131 || g_status == 130)
	{
		*u = -1;
		return ;
	}
	write (1, "> ", 2);
	content = 0;

	while (content != '\n')
	{
		if (g_status == 131 || g_status == 130)
		{
			*u = -1;
			return ;
		}
		read(0, &content, 1);
		if (j == 0 && content == doc[j])
		{
			while (content == doc[j] && content != '\n')
			{
				j++;
				if (g_status == 131 || g_status == 130)
				{
					*u = -1;
					return ;
				}
				read(0, &content, 1);
			}
			*u = writefunc(fd, doc, j, content);
		}
		else
			write(fd[0], &content, 1);
		j++;
	}
}



	// char	*heredoc;
	// char	*buf;
	// int		ret;
	
	// ret = 1;
	// while (ret == 1)
	// {
	// 	buf = readline("> ");
	// 	if (!buf)
	// 	{
	// 		write(2, "bash: warning: here-documentat line 1 delimited by end-of-file (wanted `test')", 79); //changer avec le nombre de lignes
	// 		ret = 0;
	// 	}
	// 	else if (!(ft_strcmp(buf, doc)))
	// 		ret = 0;
	// 	else
	// 		write(fd[0], buf, ft_strlen(buf));
	// 	free(buf);
	// //	buf = NULL;
	// }
	// fprintf(stderr, "ON A REUSSI A LEAVE\n");
	// return ;


int	redirect(t_list *list, int i)
{
	while (list->cmd[i])
	{
		if (ft_strcmp(list->cmd[i], "<") == 0)
		{
			if (setup_in(list->redirfd, list,
					list->cmd[i + 1], 0) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], "<<") == 0 && list->exphere != 4)
		{
			if (setup_in(list->redirfd, list,
					list->cmd[i + 1], 2) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">>") == 0)
		{
			if (setup_out(list->redirfd, list->cmd[i + 1], 1) == -1)
				return (-1);
		}
		else if (ft_strcmp(list->cmd[i], ">") == 0)
			if (setup_out(list->redirfd, list->cmd[i + 1], 0) == -1)
				return (-1);
		i++;
	}
	return (1);
}
