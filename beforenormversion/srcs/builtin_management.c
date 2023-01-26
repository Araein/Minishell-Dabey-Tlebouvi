/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:30:17 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/25 16:01:01 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checkbuiltin(t_list *list, char **env)//voir g_status pour chacun d'entres eux
{
	char	*tempoline;


	(void)env;
	if (ft_strcmp(list->cmd[0], "env") == 0)
	{
		redirectthis(list);
		printlist(list->envlist, 0);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "pwd") == 0)
	{
		redirectthis(list);
		tempoline = built_in_pwd();
		if (tempoline != NULL)
		{
			printf("%s\n", tempoline);
			free (tempoline);
		}
		g_status = 0;
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "exit") == 0)
	{
		redirectthis(list);
		built_in_exit(list);//voir pour g_status
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "unset") == 0)
	{
		redirectthis(list);
		list->envlist = unset_line(list->cmd, list->envlist, 1);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "export") == 0)
	{
		redirectthis(list);
		list->envlist = built_in_export(list->envlist, list->cmd);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "cd") == 0)
	{
		redirectthis(list);
		list->envlist = built_in_cd(list->envlist, list->cmd);
		return (1);
	}
	else if (ft_strcmp(list->cmd[0], "echo") == 0)
	{
		redirectthis(list);
		built_in_echo(list->cmd);
		return (1);
	}
	return (0);
}
/*
mieux faire pwd et exit
gerer le trick de faire cd .. dans un repo aui n'existe plus par ex 
gerer pwd quand le directeur actuel n'existe plus
*/

/*

rmdir ../dirtest3/
cd ..
->
vrai : bash: cd: ..: No such file or directory
le mien : bash: cd: ..: Stale file handle

*/
