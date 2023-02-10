/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:21:46 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/10 18:03:51 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_here(int fd, t_envlist *envlist, char *tempoline)
{

	char	**expandtab;
	char	**expanded;
	int		i;
	char	*line;

	i = 0;
	fd = open(tempoline, O_RDONLY);//secure
	while ((get_next_line(fd, &line)) > 0)
	{
		i++;
		free(line);			
	}
	close (fd);
 	expandtab = (char **)malloc(sizeof(char *) * (i + 1));
	fd = open(tempoline, O_RDONLY);
	i = 0;
	while ((get_next_line(fd, &line)) > 0)
	{
		expandtab[i] = line;
		i++;
	}
	close (fd);
	// if (expandtab[i])
	// 	free(expandtab[i]);
	expandtab[i] = NULL;
	expanded = expand_dollar(envlist, expandtab);
	// freetab(expandtab);
	i = 0;
	fd = open(tempoline, O_CREAT | O_WRONLY | O_TRUNC, 0000664);
	while (expanded[i])
	{
		write(fd, expanded[i], ft_strlen(expanded[i]));
		i++;
	}
	if (i > 0)
		write(fd, "\n", 1);
	freetab(expanded);
	close(fd);
 }

int	setup_here(char *doc, int command_num, int fd[2], t_envlist *envlist)
{
	int		u;
	int		tempostatus;
	char	*temponum;
	char	*tempoline;

	tempostatus = g_status;
	g_status = 42;//ok
	if (fd[0] > 0)
		close(fd[0]);
	temponum = ft_itoa(command_num);
	tempoline = ft_strjoin("/tmp/here_doc", temponum);//securiser
	free(temponum);
	fd[0] = open(tempoline, O_CREAT | O_WRONLY | O_TRUNC, 0000664);
	//free tempoline si pepin
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
	if (g_status == 131 || g_status == 130)
	{
		free(tempoline);
		return (-1);
	}
	
	(void)envlist;
//	expand_here(fd[0], envlist, tempoline);  // A DECOCHER POUR LEAKS GNL
	free(tempoline);
	g_status = tempostatus;
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

int	setup_in(int fd[2], t_list *list, char *doc, int type)
{
	char	*temponum;
	char	*tempoline;

	if (type == 1)
	{
		if (setup_here(doc, list->command_count, fd, list->envlist) == -1)
		{
			// fprintf(stderr, "\nerrorsetuphere = -1\n");
			return (-1);
		}
	}
	if (fd[0] > 0)
		close(fd[0]);
	if (type == 2)
	{
		temponum = ft_itoa(list->index);
		tempoline = ft_strjoin("/tmp/here_doc", temponum);//securiser
		free(temponum);
		fd[0] = open(tempoline, O_RDONLY);
		free(tempoline);
	}
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
