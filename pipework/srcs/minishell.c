/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/12/21 15:54:38 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_status;

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void	free_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	//attention au buffer vide (segfault)
	// if (tmp->buffer)
	// 	free(tmp->buffer);
	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		freetab(tmp->cmd);
		free(tmp);
		// tmp = list;
	}
}

t_list	*ft_new_node(char *cmd_i, char *buffer, t_envlist *first)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->buffer = buffer;
	new->cmd = split2(cmd_i, ' ');
	new->envlist = first;
		int k = 0;
		while (new->cmd[k])
		{
	//		printf("space ==== <%s>\n",new->cmd[k]);
			k++;
		}
	// new->cmd = ft_split(cmd_i, ' ');
	new->next = NULL;
	return (new);
}

t_list	*ft_add_node(t_list *list, char *cmd_i, char *buffer, t_envlist *envlist_first)
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	new = ft_new_node(cmd_i, buffer, envlist_first);
	if (!(list))
		list = new;
	else
	{
		head = list;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}

	return (list);
}

int	main(int argc, char **argv, char **env)
{
	int			i;
	t_list		*list;
	t_list		*tmp;
	char		*buffer;
	char		**str_cmd;
	t_envlist	*envlist_first;
	t_envlist	*tempo;
	char		*tempoline;

	(void)argc;
	(void)argv;
	buffer = NULL;
	list = NULL;
	str_cmd = NULL;
	tempoline = NULL;
	using_history();
	envlist_first = make_env(env, list);
	while ((buffer = readline("Minishell$> ")) > 0 && ft_strcmp(buffer, "exit") != 0)
	{
		add_history(buffer);
		if (check_basic_error(buffer) != 1)
		{
			free(envlist_first->shlvl_line);
			free_list_env(envlist_first);
			free_list(list);
			return (0);
		}
		// buffer = manip_quote_buffer(buffer);
		str_cmd = ft_split_pipe(buffer, '|');
		int k = 0;
		while (str_cmd[k])
		{
//			printf("pipe ==== <%s>\n", str_cmd[k]);
			k++;
		}
		i = 0;
		while(str_cmd[i] != 0)
		{
			list = ft_add_node(list, str_cmd[i], buffer, envlist_first);
			i++;
		}
		freetab(str_cmd);
		
		k= 0;

		 //gerer si env est vide... // SHLVL quand ./minishell
		(void)tempo;
		/************************************BUILT IN************************************/
		if(buffer[0] == '$')
		{
			tempo = NULL;
			if (buffer[1] == '?')
				printf("%d\n", g_status);
			else
				tempo = get_env_line(list->envlist, buffer);		//free tempo?
		}
		else if(ft_strcmp(buffer, "env") == 0)
			printlist(list->envlist, 0);
		else if(ft_strcmp(buffer, "pwd") == 0)
		{
			tempoline = built_in_pwd();
			if (tempoline != NULL)
			{
				printf("%s\n", tempoline);
				free (tempoline);
			}
			g_status = 0;
		}
		else if (buffer[0] == 'u' && buffer[1] == 'n' && buffer[2] == 's' && buffer[3] == 'e' &&
		buffer[4] == 't' && buffer[5] == ' ')
		{
			list->envlist = unset_line(ft_substr(buffer, 6, ft_strlen(buffer) - 5), list->envlist);
		}
		else if(buffer[0] == 'e' && buffer[1] == 'x' && buffer[2] == 'p' && buffer[3] == 'o' &&
		 buffer[4] == 'r' && buffer[5] == 't' && (buffer[6] == ' ' || ft_strlen(buffer) == 6))
		{
			list->envlist = built_in_export(list->envlist, buffer);
		}
		else if(buffer[0] == 'c' && buffer[1] == 'd' && buffer[2] == ' ')
		{
			list->envlist = built_in_cd(list->envlist, buffer);
		}
		else
			exec(list, env);
		//exec(buffer,/*, envlist,*/ env); //gerer si env est vide... // SHLVL quand ./minishell

		free(buffer);
		tmp = list;

		envlist_first = list->envlist;
		free_list(list);
		list = NULL;
        }
		free(envlist_first->shlvl_line); //verifier un cas ou shlvl.line n'est jamais free
		free_list_env(envlist_first);
        printf("exit : Good bye\n");
        return (0);
}
