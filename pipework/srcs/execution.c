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

	// if (checkpro(pro) == 1 && access(pro, F_OK) == 0)
	// {
	// 	pipex->islink = 1;
	// 	return (pro);
	// }
    ///////////////permet dde gerer les liens directs
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

void	dupbonus(t_list *list, int **pipefd, int type)
{
	if (type == 1)
	{
		close (pipefd[0][0]);
		dup2(pipefd[0][1], STDOUT);
		close(pipefd[0][1]);
		close_allpipe(list, pipefd, type);
	}
	if (type == 2)
	{
		close(pipefd[list->command_count - 2][1]);
		dup2(pipefd[list->command_count - 2][0], STDIN);
		close(pipefd[list->command_count - 2][0]);
		close_allpipe(list, pipefd, type);
	}
	if (type == 3)
	{
		close(pipefd[list->index - 1][1]); 
		dup2(pipefd[list->index - 1][0], STDIN);
		close(pipefd[list->index - 1][0]);
		close(pipefd[list->index][0]);
		dup2(pipefd[list->index][1], STDOUT);
		close(pipefd[list->index][1]);
		close_allpipe(list, pipefd, type);
	}
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

int	errorpid(int *pipefd[2], int command_count)
{

	if(pipefd)
		freeandclose(NULL, pipefd, command_count, 1);
	perror("Error");
	g_status = -1;//??????
	return (-1);
}

int	firstchild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
	 	return (errorpid(pipefd, list->command_count));
	if (p_pid == 0)
	{
		paths = getpath(list->cmd[0], getmyline(env)); //secure
		// if (!paths)
		// 	return (patherror(pro, pipex->fd[0], pipefd[0], pipefd[1])); //secure
		dupbonus(list, pipefd, 1);
		execve(paths, list->cmd, env);
	//	fprintf(stderr, "\nFIRST EXECVE A FOIRE\n");
		//execerror(pro, paths, pipex);
	}
	// list->index++;
	return (0);
}

int	middlechild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd, list->command_count));
	if (p_pid == 0)
	{
		paths = getpath(list->cmd[0], getmyline(env)); //secure
		// if (!paths)
		// 	return (patherrormid(pro, /*pipex->fd[0],*/ pipefd[0], pipefd[1]));
		dupbonus(list, pipefd, 3);
		execve(paths, list->cmd, env);
		//execerror(pro, paths, pipex);
	//	fprintf(stderr, "\nMIDDLE EXECVE A FOIRE\n");

	}
	return (0);
}

int	lastchild(t_list *list, int **pipefd, char **env)
{
	pid_t	p_pid;
	char	*paths;	

	p_pid = fork();
	if (p_pid < 0)
		return (errorpid(pipefd, list->command_count));
	if (p_pid == 0)
	{
		paths = getpath(list->cmd[0], getmyline(env)); //secure
		// if (!paths)
		// 	return (patherror(pro, pipex->fd[1], pipefd[0], pipefd[1]));
		dupbonus(list, pipefd, 2);
		execve(paths, list->cmd, env);
	//	fprintf(stderr, "\nLAST EXECVE A FOIRE\n");
		//execerror(pro, paths, pipex);
	}
	return (0);
}



void    exec(t_list *list, char **env)
{
	int		command_count;
	int		i;
	int		index;
	int		**pipefd;
	int		p_pid;
	t_list	*tempo;
	char	*paths;

	index = 0;
	tempo = list;
	command_count = 0;
	pipefd = NULL; //attentionfaire attention si c'est pas nul
	while(list)
	{
		command_count++;
		list = list->next;
	}
	list = tempo;
	if (command_count > 1)
	{
		list->index = index;
		list->command_count = command_count;
		pipefd = mallocandpipe(command_count); //malloc et pipe les fd qui seront utilises // a securiser
		i = 0;

		while (i < command_count)
		{
			fprintf(stderr, "command = %d | index = %d\n", list->command_count, list->index);
			if (index == 0)
			{
				if (firstchild(list, pipefd, env) == -1)
				{
					freeandclose(list, pipefd, command_count, 1); //pas -1?
					return ;// (-1);
				}
				close(pipefd[0][1]);
				index++;
			}
			else if (index > 0 && index < command_count - 1)
			{
				if (middlechild(list, pipefd, env) == -1)
				{
					freeandclose(list, pipefd, command_count, 1);
					return ;
				}
				close(pipefd[index][1]);
				// close(pipefd[index - 1][1]);
				
				//close(pipefd[pipex->index - 1][0]);//pas faire quand ca foire (mettre dans middlechild?)
				//closefd(pipefd[pipex->index - 1][0], pipefd[pipex->index - 1][1], -1);//, pipefd[pipex->index][1]);
				index++; //verifier un retour -1?
			}
			else
			{
				if (lastchild(list, pipefd, env) == -1) //VERFIER UN RETOUR -1?
				{
					freeandclose(list, pipefd, command_count, -1);
					return ;//(-1);
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
		while(i < command_count)	
		{
			waitpid (-1, NULL, 0);
			i++;
		}
	}
	else
	{
		//checker le cas ou il y a 0 commandes
		p_pid = fork(); //faire un retour d'erreur si (p_pid < 0)
		if (p_pid == -1)
		{
			errorpid(pipefd, command_count);
			return ;
		}
		
		if (p_pid == 0)
		{
			//commandline = ft_split(buffer, ' '); //securiser le retour du split
			paths = getpath(list->cmd[0], getmyline(env)/*, pipex*/); //faire une retour d'erreur si !PATH		
			execve(paths, list->cmd, env); //gerer erreur
			// freetab(commandline);
			free(paths);
		}
			waitpid (-1, NULL, 0);
	}
}
