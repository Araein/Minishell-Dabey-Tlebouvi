/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 18:45:48 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

int	ft_prompt(char **buffer)
{
	*buffer = readline("Minishell$> ");
	if (!(*buffer))
		return (1);
	add_history(*buffer);
	return (0);
}

t_list	*else_while_func(t_list_prov *list_prov, t_list *list, char *buffer)
{	
	int	i;

	i = 0;
	list_prov->str_cmd = ft_split_pipe(buffer, '|', 0);
	list_prov->str_cmd = expand_dollar(list_prov->envlist,
			list_prov->str_cmd);
	while (list_prov->str_cmd[i] != 0)
	{
		list = ft_add_node(list, list_prov->str_cmd[i], buffer,
				list_prov->envlist);
		i++;
	}
	list_prov->envlist = list->envlist;
	freetab(list_prov->str_cmd);
	free(buffer);
	get_clean_string(list, 0, 0);
	return (list);
}

void	loop(t_list_prov *list_prov, t_list *list, char **env)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		if (ft_prompt(&buffer))
			break ;
		if (check_basic_error(buffer) != 1)
			free_first_check(list);
		else
		{
			list = else_while_func(list_prov, list, buffer);
			if ((list->cmd[0] != NULL && exec(list, env) == -1))
			{
				close_here(list);
				free_list(list);
				list = NULL;
				break ;
			}
			free_list(list);
			list = NULL;
		}
	}
}

t_list_prov	*ft_init_list_prov(t_list_prov *list_prov, char **argv)
{
	(void)argv;
	g_status = 0;
	list_prov = malloc(sizeof(t_list_prov));
	if (!list_prov)
		return (NULL);
	list_prov->str_cmd = NULL;
	return (list_prov);
}

int	main(int argc, char **argv, char **env)
{
	t_list		*list;
	t_list_prov	*list_prov;

	list = NULL;
	list_prov = NULL;
	if (argc != 1)
	{
		printf("error : too many arguments\n");
		exit(1);
	}
	list_prov = ft_init_list_prov(list_prov, argv);
	using_history();
	list_prov->envlist = make_env(env);
	loop(list_prov, list, env);
	if (list_prov->envlist->shlvl_line)
		free(list_prov->envlist->shlvl_line);
	free_list_env(list_prov->envlist);
	free(list_prov);
	exit(g_status);
	return (0);
}
