/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2023/01/26 15:44:42 by tlebouvi         ###   ########.fr       */
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
	new->clean_string = NULL;
	new->redirfd[0] = 0;
	new->redirfd[1] = 0;
	new->to_unlink = NULL;
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
		head->clean_tab = ft_split(head->clean_string, ' ');
		if(head->clean_string)
			free(head->clean_string);
		head = head->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	int			i;
	t_list		*list;
	char		*buffer;
	char		**str_cmd;
	t_envlist	*envlist_first;
	// char		*tempoline;
	int			allgood;
	t_token		*token;
	char		*tofreeshlvl;

	allgood = 0;
	(void)argv;
	buffer = NULL;
	list = NULL;
	str_cmd = NULL;
	// tempoline = NULL;
	g_status = 0;
	token = NULL;
	if (argc != 1)
	{
		printf("error : too many arguments\n");
		g_status = 1;
		exit(1);
	}
	using_history();
	envlist_first = make_env(env, list);
	tofreeshlvl = envlist_first->shlvl_line;
	while ((buffer = readline("Minishell$> ")) > 0)
	{
		add_history(buffer);
		if (check_basic_error(buffer) != 1)
		{
			g_status = 1;
			free_list(list);
		}
		else
		{
			str_cmd = ft_split_pipe(buffer, '|');
			// token = ft_creat_token(&token, str_cmd);/////////////////////
			// printlist_token(token);/////////////////////
			str_cmd = expand_dollar(envlist_first, str_cmd);
			i = 0;
			while(str_cmd[i] != 0)
			{
				list = ft_add_node(list, str_cmd[i], buffer, envlist_first);
				i++;
			}
			freetab(str_cmd);
			get_clean_string(list);

			if ((list->cmd[0] != NULL && exec(list, env) == -1))
			{
				close_here(list); // a tester
				free(buffer);
				envlist_first = list->envlist;
				free_list(list);
				list = NULL;
				allgood = 1;
				break;
			}//exec(buffer,/*, envlist,*/ env); //gerer si env est vide... // SHLVL quand ./minishell

			free(buffer);
			envlist_first = list->envlist;
			free_list(list);
			list = NULL;			
		}

    }
	if (tofreeshlvl)
		free(tofreeshlvl); //verifier un cas ou shlvl.line n'est jamais free
	free_list_env(envlist_first);
	// if (allgood == 0)
	// 	printf("exit\n");
//	printf("\ng_status2 = %d\n", g_status);
	exit(g_status);
	return (0);
}
/*
-> verifier si c'est un here doc (<<) ou une autre redirection ( < >> >)
si c'est here doc -> verifier que apres il y a qqch autre que pipe ou autre redir
si c'est redir -> verifier 

*/