/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:21:46 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/30 20:48:34 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_here(char *doc, char *to_unlink, int fd[2])
{
	int		u;

	if (to_unlink)
		unlink(to_unlink);
	if (fd[0] > 0)
		close(fd[0]);
	fd[0] = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000664);
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
	int	i;

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

int	setup_in(int fd[2], char *to_unlink, char *doc, int type)
{
	if (type == 1)
		setup_here(doc, to_unlink, fd);
	if (fd[0] > 0)
		close(fd[0]);
	if (type == 2)
		fd[0] = open("/tmp/here_doc", O_RDONLY);
	else if (type == 0)
		fd[0] = open(doc, O_RDONLY);
	if (fd[0] < 0)
	{
		perror(doc);
		g_status = 1;
		return (-1);
	}
	return (1);
}

int	lenght_of_word(char *s, char sep)
{
	int		len_w;
	char	quote_tp;

	len_w = 0;
	while (*s && *s != sep)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			len_w++;
			quote_tp = *s;
			s++;
			loop_word_quote(&len_w, s, quote_tp);
			s++;
			len_w++;
		}
		else if (*s && *s != sep)
		{
			while (*s && *s != '\'' && *s != '\"' && *s != sep)
			{
				len_w++;
				s++;
			}
		}
	}
	return (len_w);
}
