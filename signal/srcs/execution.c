/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:40:31 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/02/10 20:02:37 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*minifreetab(char **tab, char *result)
{
	freetab(tab);
	return (result);
}

int	cdsolo(t_list *list, int savedin, int savedout)
{
	if (ft_strcmp(list->clean_tab[0], "cd") == 0)
	{
		if (callredirec(list, NULL, 4) == -1 || list->cmd[0] == NULL)
			return (closesaved(list, savedout, savedin, 1));
		list->envlist = built_in_cd(list->envlist, list->cmd, 0);
		return (closesaved(list, savedout, savedin, 0));
	}
	close (savedout);
	close(savedin);
	return (1);
}

int	exportunset(t_list *list)
{
	int	saved[2];

	saved[0] = dup(1);
	saved[1] = dup(0);
	if (ft_strcmp(list->clean_tab[0], "export") == 0)
	{
		if (callredirec(list, NULL, 4) == -1 || list->cmd[0] == NULL)
			return (closesaved(list, saved[0], saved[1], 1));
		list->envlist = built_in_export(list->envlist, list->cmd);
		return (closesaved(list, saved[0], saved[1], 0));
	}
	if (ft_strcmp(list->clean_tab[0], "unset") == 0)
	{
		if (callredirec(list, NULL, 4) == -1 || list->cmd[0] == NULL)
			return (closesaved(list, saved[0], saved[1], 1));
		list->envlist = unset_line(list->cmd, list->envlist, 1);
		return (closesaved(list, saved[0], saved[1], 0));
	}
	return (cdsolo(list, saved[1], saved[0]));
}

int	checkerrorcmd(t_list *list)
{
	if (ft_strcmp(list->clean_tab[0], "exit") == 0)
	{
//		fprintf(stderr, "passe ici 1\n");
		// if ( == -1)
		// 	return (-2);
		redirectthis(list);
//		fprintf(stderr, "passe ici 2\n");
		freetab(list->cmd);
		list->cmd = list->clean_tab;
		list->clean_tab = NULL;
		built_in_exit(list, 0);
		close_here(list);
		write(2, "exit\n", 5);
		return (-1);
	}	
	return (1);
}

int	errorpathorwait(t_list *list, int type, char **myenv, char *paths)
{
	int	status;

	if (type == 1 || type == 3)
	{
		if (type == 1)
		{
			write(2, "minishell: ", 11);
			write(2, list->cmd[0], ft_strlen(list->cmd[0]));
			write(2, ": command not found\n", 20);
			g_status = 127;
		}
		if (type == 3)
		{
			write(2, "minishell: ", 11);
			write(2, paths, ft_strlen(paths));
			write(2, ": Is a directory\n", 17);
			closedir(list->isdir);
			free(paths);
			g_status = 126;
		}
		if (myenv)
			freetab(myenv);

		return (-1);
	}
	else if (type == 2)
	{
		waitpid (-1, &status, 0);
	//	fprintf(stderr, "status = %d gstatus = %lld\n", status, g_status);
//		if (status != 130 && status != 131)
		if (list->statushandle == 0 && ((status == 0 && g_status == 130) || (status == 0 && g_status == 131)))
		{
			list->statushandle++;
			return (1);
		}
		list->statushandle = 0;
		g_status = status / 256;
		return (1);
	}
	return (0);
}
