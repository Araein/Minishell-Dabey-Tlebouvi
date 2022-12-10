/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2022/12/10 16:24:18 by tlebouvi         ###   ########.fr       */
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

t_list	*ft_new_node(char *cmd_i, char *buffer)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->buffer = buffer;
	// new->cmd = ft_split_space(cmd_i, ' ');
	new->cmd = ft_split(cmd_i, ' ');
	new->next = NULL;
	return (new);
}

t_list	*ft_add_node(t_list *list, char *cmd_i, char *buffer)
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	new = ft_new_node(cmd_i, buffer);
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
	//int			j;
	int			i;
	t_list		*list;
	//t_list		*tmp;
	char		*buffer;
	char		**str_cmd;
	t_envlist	*envlist;
	t_envlist	*tempo;
	char		*tempoline;
	// char		**tempotab;

	(void)argc;
	(void)argv;
	buffer = NULL;
//	list = NULL;
	str_cmd = NULL;
	envlist = NULL;
	tempoline = NULL;
	using_history();
	envlist = make_env(env, list);
	while ((buffer = readline("Minishell$> ")) > 0 && ft_strcmp(buffer, "exit") != 0)
	{
		add_history(buffer);
		// if (check_basic_error(buffer) != 1)
		// 	return (0);
		// str_cmd = ft_split_quote(buffer, '|');
		// int k = 0;
		// while (str_cmd[k])
		// {
		// 	printf("pipe ==== %s\n", str_cmd[k]);
		// 	k++;
		// }
		i = 0;
		// while(str_cmd[i] != 0)
		// {
		// 	list = ft_add_node(list, str_cmd[i], buffer);
		// 	i++;
		// }
		if(buffer[0] == '$')
		{
			tempo = NULL;
			if (buffer[1] == '?')
				printf("%d\n", g_status);
			else
				tempo = get_env_line(envlist, buffer);		//free tempo?
		}
		else if(ft_strcmp(buffer, "env") == 0)
			printlist(envlist, 0);
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
			envlist = unset_line(ft_substr(buffer, 6, ft_strlen(buffer) - 5), envlist);
		}
		else if(buffer[0] == 'e' && buffer[1] == 'x' && buffer[2] == 'p' && buffer[3] == 'o' &&
		 buffer[4] == 'r' && buffer[5] == 't' && (buffer[6] == ' ' || ft_strlen(buffer) == 6))
		{
			envlist = built_in_export(envlist, buffer);
		}
		else if(buffer[0] == 'c' && buffer[1] == 'd' && buffer[2] == ' ')
		{
			envlist = built_in_cd(envlist, buffer);
		}
		else
			exec(buffer,/*, envlist,*/ env); //gerer si env est vide... // SHLVL quand ./minishell
		free(buffer);
		// tmp = list;
		// while (tmp != 0)
		// {
		// 	printf("\n\nnew\n");
		// 	j = 0;
		// 	while (tmp->cmd[j] != 0)
		// 	{
		// 		printf("cmd = %s\n",tmp->cmd[j]);
		// 		j++;
		// 	}
		// 	tmp = tmp->next;
		// }
		// freetab(str_cmd);
		// free_list(list);
		// list = NULL;
        }


		// i = 0;
		// while (env[i])
		// {
		// 	printf("La ligne %d de env est: .%s.\n\n", i, env[i]);
		// 	i++;
		// }

		
        // free_history_entry();
//		free(list.shlvl_line);
		free_list_env(envlist);
        printf("exit : Good bye\n");
        //free_list(list);
        return (0);
}
