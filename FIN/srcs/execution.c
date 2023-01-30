/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:40:31 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/30 16:21:16 by tlebouvi         ###   ########.fr       */
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
	int	savedout;
	int	savedin;

	savedout = dup(1);
	savedin = dup(0);
	if (ft_strcmp(list->clean_tab[0], "export") == 0)
	{
		if (callredirec(list, NULL, 4) == -1 || list->cmd[0] == NULL)
			return (closesaved(list, savedout, savedin, 1));
		list->envlist = built_in_export(list->envlist, list->cmd);
		return (closesaved(list, savedout, savedin, 0));
	}
	if (ft_strcmp(list->clean_tab[0], "unset") == 0)
	{
		if (callredirec(list, NULL, 4) == -1 || list->cmd[0] == NULL)
			return (closesaved(list, savedout, savedin, 1));
		list->envlist = unset_line(list->cmd, list->envlist, 1);
		return (closesaved(list, savedout, savedin, 0));
	}
	return (cdsolo(list, savedin, savedout));
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
		built_in_exit(list, 0);
		close_here(list);
		write(2, "exit\n", 5);
		return (-1);
	}	
	return (1);
}

int	errorpathorwait(t_list *list, int type)
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
