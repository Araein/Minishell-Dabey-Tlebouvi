/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2023/01/23 20:16:54 by tlebouvi         ###   ########.fr       */
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
	while (list != NULL)
	{
		if (list->redirfd[0] > 0)
			close(list->redirfd[0]);
		if (list->redirfd[1] > 0)
			close(list->redirfd[1]);
		tmp = list;
		list = list->next;
		if (tmp->cmd)
			freetab(tmp->cmd);
		if(tmp->clean_tab)
		 	freetab(tmp->clean_tab);
		free(tmp);
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
		// int k = 0;
		// while (new->cmd[k])
		// {
		// 	printf("space ==== <%s>\n",new->cmd[k]);
		// 	k++;
		// }
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

int	is_redi(char *line, int i)
{
    if (line[i] == '>')
    {
        if (line[++i] == '>')
            return (2);
        else
            return (1);
    }
    else if (line[i] == '<')
    {
        if (line[++i] == '<')
            return (2);
        else
            return (1);
    }
    return (0);
}

void    get_clean_string(t_list *list)
{
	int		i;
	int		j;
	int		redi_type;
	char	*clean_str;
	char	*tempo;
	char	*tempo2;
	t_list	*head;

	i = 0;
	head = list;
	redi_type = 0;
	clean_str = NULL;
	head->clean_string = NULL;
	head->clean_tab = NULL;
	if (!list)
		return ;
	while (head != 0)
	{

		i = 0;
		while (head->cmd[i])
		{		
			tempo = NULL;
			tempo2 = NULL;
			head->clean_string = NULL;
			head->clean_tab = NULL;
			j = 0;
			while (head->cmd[i] && is_redi(head->cmd[i], j))
				i += 2;

			while (head->cmd[i])
			{
				if (is_redi(head->cmd[i], j) == 0)
				{
					if (head->clean_string)
						tempo = ft_strjoin(head->clean_string, " ");
					head->clean_string = ft_strjoin(tempo, head->cmd[i]);
					
					
					if (tempo)
						free(tempo);				
					
					if (tempo2)
						free(tempo2);
					tempo2 = head->clean_string;
				}
				else
					i++;
				i++;	
			}
		}
		// fprintf(stderr, "\n\n\nLA CLEAN STRING = %s\n", head->clean_string);
		head->clean_tab = ft_split(head->clean_string, ' ');
		if(head->clean_string)
			free(head->clean_string);
		head = head->next;
	}
}
/*
ou initaliser les valeurs de chaque maillon de la chaine
list->redirfd[0] = 0;
list->redirfd[1] = 0;

*/
int	main(int argc, char **argv, char **env)
{
	int			i;
	t_list		*list;
	t_list		*tmp;
	char		*buffer;
	char		**str_cmd;
	t_envlist	*envlist_first;
	char		*tempoline;
	int			allgood;
	char		*tofreeshlvl;

	allgood = 0;
	(void)argv;
	buffer = NULL;
	list = NULL;
	str_cmd = NULL;
	tempoline = NULL;
	if (argc != 1)
	{
		printf("error : too many arguments\n");
		g_status = 1;
		exit(1);
	}
	using_history();
	envlist_first = make_env(env, list);
	tofreeshlvl = envlist_first->shlvl_line;
	while ((buffer = readline("Minishell$> ")) > 0/* && ft_strcmp(buffer, "exit") != 0*/)
	{
		add_history(buffer);
		if (check_basic_error(buffer) != 1)
		{
			free(tofreeshlvl);
			free_list_env(envlist_first);
			list->to_unlink = NULL;
			list->redirfd[0] = 0;
			list->redirfd[1] = 0;
			free_list(list);
			return (0);
		}
		str_cmd = ft_split_pipe(buffer, '|');
		str_cmd = expand_dollar(envlist_first, str_cmd);
		// int k = 0;
		// while (str_cmd[k])
		// {
		// 	printf("pipe ==== <%s>\n", str_cmd[k]);
		// 	k++;
		// }
		i = 0;
		while(str_cmd[i] != 0)
		{
			list = ft_add_node(list, str_cmd[i], buffer, envlist_first);
			i++;
		}
		freetab(str_cmd);
		get_clean_string(list);

		// if(buffer[0] == '$')
		// {
		// 	tempo = NULL;
		// 	if (buffer[1] == '?')
		// 		printf("%d\n", g_status);
		// 	else
		// 		tempo = get_env_line(list->envlist, buffer);		//free tempo?
		// }
		// else

		if ((list->cmd[0] != NULL && exec(list, env) == -1))
		{
			close_here(list); // a tester

			free(buffer);
			tmp = list;
//			list->envlist->shlvl_line = envlist_first->shlvl_line;
			envlist_first = list->envlist;
			free_list(list);
			list = NULL;
			allgood = 1;
			break;
		}//exec(buffer,/*, envlist,*/ env); //gerer si env est vide... // SHLVL quand ./minishell

		free(buffer);
		tmp = list;
//		list->envlist->shlvl_line = envlist_first->shlvl_line;
		envlist_first = list->envlist;
		free_list(list);
		list = NULL;
    }
//	fprintf(stderr, "\nERROR = %d\n", g_status);
	if (tofreeshlvl)
		free(tofreeshlvl); //verifier un cas ou shlvl.line n'est jamais free
	free_list_env(envlist_first);
	if (allgood == 0)
		printf("exit : Good bye\n");
	exit(g_status);
	return (0);
}
