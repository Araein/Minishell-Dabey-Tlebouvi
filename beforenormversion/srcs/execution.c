/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:40:31 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/25 21:20:24 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getmyline(char **env)
{
	int		i;
	int		j;
	char	*goodline;

	j = 0;
	i = 0;
	goodline = "PATH=";
	while (env[i])
	{
		while (env[i][j] == goodline[j] && j < 5)
			j++;
		if (j == 5)
			return (env[i] + 5);
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}

char	*minifreetab(char **tab, char *result)
{
	freetab(tab);
	return (result);
}

int	checkpro(char *pro)
{
	int	i;

	i = 0;
	while (i < ft_strlen(pro))
	{
		if (pro[i] == '/')
			return (1);
		i++;
	}
	return (-1);
}

char	*getpath(char *pro, char *goodline)
{
	char	**paths;
	char	**tempo;
	char	*tmp;
	char	*result;

	if (checkpro(pro) == 1 && access(pro, F_OK) == 0)
		return (ft_strdup(pro));
	if (goodline == NULL)
		return (NULL);
	paths = ft_split(goodline, ':');
	tempo = paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		result = ft_strjoin(tmp, pro);
		free(tmp);
		if (access(result, F_OK) == 0)
			return (minifreetab(tempo, result));
		free(result);
		paths++;
	}
	freetab(tempo);
	return (NULL);
}

// void	print_pipe_content(int pipefd)
// {
// 	int i;
// 	char c;
// 	i = 0;
// 	fprintf(stderr, "\n\nPIPE CONTENT =");
// 	fprintf(stderr, "..");
// 	while (read(pipefd, &c, 1) && i < 6)
// 	{
// 		fprintf(stderr, "%c", c);
// 		i++;
// 	}
// 	fprintf(stderr,"..");
// 	fprintf(stderr, "\n\n");
// }

int	**mallocandpipe(int command_count)
{
	int	i;
	int	**pipefd;

	i = 0;
	pipefd = (int **)malloc((command_count - 1) * sizeof(int *)); //a securiser
	i = 0;
	while (i < (command_count - 1))
	{
		pipefd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < command_count - 1)
	{
		if (pipe(pipefd[i]) == -1) //a securiser
			perror ("Error");
		i++;
	}
	return (pipefd);
}

void	close_allpipe(t_list *list, int **pipefd, int type)
{
	int		i;

	i = 0;
	if (type == 1)
	{
		i = 1;
		while ( i < (list->command_count - 1))
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if (type == 2)
	{
		i = 0;
		while ( i < list->command_count - 2)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			i++;
		}
	}
	else if ( type == 3)
	{
		i = 0;
		while ( i < list->command_count - 1)
		{
			if (i != list->index - 1)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
			i++;
		}
	}
}

int	firstchild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;
	int		error;

	p_pid = fork();
	// if (p_pid < 0)
	// 	return (errorpid(pipefd)); //a secure
	if (p_pid == 0)
	{
		error = redirectthis(list);


		freetab(list->cmd);
		list->cmd = NULL;
		list->cmd = list->clean_tab;
		list->clean_tab = NULL;
		dupbonus(list, pipefd, 1);
		
		if (error == -1)
			return (-1);


		if (checkbuiltin(list, env) == 0)
		{
			paths = getpath(list->cmd[0], getmyline(env)); //secure
			if (!paths)
			{
				write (2,list->cmd[0], ft_strlen(list->cmd[0]));
				write (2,": command not found\n", 20);
				g_status = 127;
				return (-1);
			}
			execve(paths, list->cmd, env); //a secure
		}
		return (-1);// exit(EXIT_SUCCESS);//execerror(pro, paths, pipex);
	}
	return (0);
}

int	middlechild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;
	int		error;

	p_pid = fork(); // a secure !
	// if (p_pid < 0)
	//  	return (-1);
	if (p_pid == 0)
	{


		error = redirectthis(list);
		freetab(list->cmd);
		list->cmd = NULL;
		list->cmd = list->clean_tab;
		list->clean_tab = NULL;
		dupbonus(list, pipefd, 3);
		if (error == -1)
			return (-1);
		if (checkbuiltin(list, env) == 0)
		{
			paths = getpath(list->cmd[0], getmyline(env)); //secure
			if (!paths)
			{
				write(2,list->cmd[0], ft_strlen(list->cmd[0]));
				write(2,": command not found\n", 20);
				g_status = 127;
				return (-1);
			}
			execve(paths, list->cmd, env);
			//execerror(pro, paths, pipex);
		}
		return (-1);//fprintf(stderr, "\nMIDDLE EXECVE A FOIRE\n");
	}
	return (0);
}

int	lastchild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;
	int		error;

	p_pid = fork();
	// if (p_pid < 0)
	// 	return (errorpid(pipefd));
	
	if (p_pid == 0)
	{
		error = redirectthis(list);//gerer retour -1 !!!!

		freetab(list->cmd);
		list->cmd = NULL;
		list->cmd = list->clean_tab;
		list->clean_tab = NULL;
		dupbonus(list, pipefd, 2);
		
		if (error == -1)
			return (-1);


		if (checkbuiltin(list, env) == 0)
		{
			paths = getpath(list->cmd[0], getmyline(env)); //secure
			if (!paths)
			{
				write(2,list->cmd[0], ft_strlen(list->cmd[0]));
				write(2,": command not found\n", 20);
				g_status = 127;
				return (-1);
			}
			execve(paths, list->cmd, env);
		//	fprintf(stderr, "\nLAST EXECVE A FOIRE\n");
		}
		return (-1);//execerror(pro, paths, pipex);
	}
	return (0);
}

void	freeandclose(t_list *list, int **pipefd, int command_count, int type)
{
	int	j;
	int	i;

	if (type != -1)
	{
		j = 0;
		while (j < command_count - 1)
		{
			close(pipefd[j][0]);
			close(pipefd[j][1]);
			j++;
		}
	}
	if (type != 2)
	{
		i = 0;
		while (i < command_count - 1)
		{
			free(pipefd[i]);
			i++;
		}
		free(pipefd);
	}
	(void)list;
}

// void printmytab(char **tab)
// {
// 	int i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		fprintf(stderr, "%s\n", tab[i]);
// 		i++;
// 	}
// 	fprintf(stderr, "\n");
// }

int    exec(t_list *list, char **env)
{
	int		command_count;
	int		i;
	int		index;
	int		p_pid;
	int		**pipefd;
	int		status;
	t_list	*tempo;
	char	*paths;

	index = 0;
	tempo = list;
	command_count = 0;
	status = 0;

	
	while (list)
	{
		i = 0;
		list->to_unlink = NULL;
		list->redirfd[0] = 0;
		list->redirfd[1] = 0;
		list->exit = 0;
		while (list->cmd[i])
		{
			if (ft_strcmp(list->cmd[i], "<<") == 0)
				setup_in(list->redirfd, list->to_unlink, list->cmd[i + 1], 1); //ouvrir tous les heredoc
			i++;
		}
		command_count++;
		list = list->next;
	}

	
	list = tempo;
	if (command_count > 1)
	{
		list->index = index;
		list->command_count = command_count;
		pipefd = mallocandpipe(command_count);// a securiser
		i = 0;
		while (i < command_count)
		{
			if (index == 0)
			{
				if (firstchild(list, pipefd, env) == -1)
				{
					freeandclose(list, pipefd, command_count, 1);
					return (-1);
				}
				close(pipefd[0][1]);
				index++;
			}
			else if (index > 0 && index < command_count - 1)
			{
				if (middlechild(list, pipefd, env) == -1)
				{
					freeandclose(list, pipefd, command_count, 1);
					return (-1);
				}
				close(pipefd[index][1]);
				index++;
			}
			else
			{
				if (lastchild(list, pipefd, env) == -1)
				{
					freeandclose(list, pipefd, command_count, -1);
					return (-1);
				}
				freeandclose(list, pipefd, command_count, 1);
				index++;
			}
			i++;
			if (index < command_count)
			{
				list = list->next;
				list->index = index;
				list->command_count = command_count;
			}
		}
		i = 0;
//		g_status = 0;
		while (i < command_count)
		{
			waitpid (-1, &status, 0);
			g_status = status / 256;
			i++;
		}
	//	
	}
	else
	{			
		if (ft_strcmp(list->clean_tab[0], "exit") == 0)
		{
			redirectthis(list);
			freetab(list->cmd);
			list->cmd = list->clean_tab;
			list->clean_tab = NULL;
			built_in_exit(list);
			close_here(tempo);
			write(2, "exit\n", 5);
			return (-1);
		}
		p_pid = fork(); //faire un retour d'erreur si (p_pid < 0)
		if (p_pid == 0)
		{
			
			command_count = redirectthis(list);
			freetab(list->cmd);
			list->cmd = list->clean_tab;
			list->clean_tab = NULL;
			if (command_count == -1)
				return (-1);
			if (checkbuiltin(list, env) == 0)
			{
				paths = getpath(list->cmd[0], getmyline(env)); //faire une retour d'erreur si !PATH
				if (!paths)
				{
					write(2,list->cmd[0], ft_strlen(list->cmd[0]));
					write(2,": command not found\n", 20);
					g_status = 127;
					return (-1); //(ajouter message)
				}
				execve(paths, list->cmd, env); //gerer erreur
				free(paths);
				return (-1);
			}
			//freeandclose(list, pipefd, command_count, 1);
			return (-1);
		}
//		printf("\ng_status = %d\n", g_status);
//		g_status = 0;
		waitpid (-1, &status, 0);
		g_status = status / 256;
		//printf("\nstatus = %d\n", status);

		
	}
	close_here(tempo);
	return (1);
}

void close_here(t_list *tempo)
{
	int	i;
//	close(tempo->redirfd[0]);
	while (tempo)
	{
		i = 0;
		while (tempo->cmd[i])
		{
			if (ft_strcmp(tempo->cmd[i], "<<") == 0)
				unlink(tempo->cmd[i + 1]);
			i++;
		}
//		close (tempo->redirfd[0]);
		tempo = tempo->next;
	}
	return ;
}


/*
tlebouvi@e3r5p7:~$ echo $?
130
tlebouvi@e3r5p7:~$ ^C
tlebouvi@e3r5p7:~$ echo $?
130
tlebouvi@e3r5p7:~$ bonjour
bonjour: command not found
tlebouvi@e3r5p7:~$ echo $?
127
*/

//gerer les builtin avec les redirections

/*
ne fonctionne pas
<< stop cat > testfile | < testfile grep salut > result


car essaye de lire testfile avant qu'il ne soit cree

comparer les resultats de 
<< stop1 cat > result1 | << stop2 cat > result2
-> overlaping heredoc

testerles conflits potentiels entre les redirections et els pipes

gerer erreurs d'ouverture de document


faire un pre parsing des here doc -> creer les files de here doc normalement 
-> traiter ensuite les files de heredoc comme des files "normales" mais a supprimer



A GERER VITE AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
echo bonjour ca va bien > file

*/