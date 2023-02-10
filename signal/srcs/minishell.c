/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:05:27 by dabey             #+#    #+#             */
/*   Updated: 2023/02/10 20:08:52 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long	g_status;

int	ft_prompt(char **buffer)
{
	*buffer = readline("Minishell$> ");
	if (!(*buffer))
	{
		write (2, "exit\n", 5);
		return (1);
	}
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

void	handle_sig(int sig)
{
	int					status;
	struct sigaction	sb;

	status = 0;
	waitpid(-1, &status, 0);
//	fprintf(stderr, "\nstatus dans handle = %d\n", status);
	if (!status && g_status != 42)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig != SIGQUIT)
		write(2, "\n", 1);


	if (sig == SIGINT)
		g_status = 130;
	else if (sig == SIGQUIT)
	{
		g_status = 131;
		write(2,"Quit (core dumped)\n", 19);
	}
//	fprintf(stderr, "\ng_status dans handle2 = %lld\n", g_status);

	sb.sa_handler = SIG_IGN;
	sigemptyset(&sb.sa_mask);
	sigaddset(&sb.sa_mask, SIGQUIT);
	sb.sa_flags = 0;
	if (sigaction(SIGQUIT, &sb, NULL) == -1)
		return ;
}

// attention bien recup g_status apres cat | cat | cat
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
			list->statushandle = list_prov->statushandle;
			if ((list->cmd[0] != NULL && exec(list, env) == -1))
			{
				free_list(list);
				list = NULL;
				break ;
			}
			list_prov->statushandle = list->statushandle;
			list_prov->envlist = list->envlist;
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
	list_prov->statushandle = 0;
	return (list_prov);
}

int	main(int argc, char **argv, char **env)
{
	t_list				*list;
	t_list_prov			*list_prov;
	struct sigaction	sa;
	struct sigaction	sb;


	sa.sa_handler = &handle_sig;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = 0;

	sb.sa_handler = SIG_IGN;
	sigemptyset(&sb.sa_mask);
	sigaddset(&sb.sa_mask, SIGQUIT);
	sb.sa_flags = 0;

	list = NULL;
	list_prov = NULL;
	if (argc != 1)
	{
		write(2, "error : too many arguments\n", 27);
		exit(1);
	}
	list_prov = ft_init_list_prov(list_prov, argv);
	using_history();
	list_prov->envlist = make_env(env);



	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		if (list_prov && list_prov->envlist && list_prov->envlist->shlvl_line)
			free(list_prov->envlist->shlvl_line);
		if (list_prov)
			free_list_env(list_prov->envlist);
		free(list_prov);
		exit(g_status);//update g status avec perror
	}

	if (sigaction(SIGQUIT, &sb, NULL) == -1)
	{
		if (list_prov && list_prov->envlist && list_prov->envlist->shlvl_line)
			free(list_prov->envlist->shlvl_line);
		if (list_prov)
			free_list_env(list_prov->envlist);
		free(list_prov);
		exit(g_status);//update g status avec perror
	}



	loop(list_prov, list, env);
	if (list_prov && list_prov->envlist && list_prov->envlist->shlvl_line)
		free(list_prov->envlist->shlvl_line);
	if (list_prov)
		free_list_env(list_prov->envlist);
	free(list_prov);
	exit(g_status);
	return (0);
}
