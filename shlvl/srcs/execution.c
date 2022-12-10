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

char	*getpath(char *pro, char *goodline/*, t_pipe *pipex*/)
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

// int	patherror(char **pro, int fd, int pipefd1, int pipefd2)
// {
// 	ft_putstr_fd("zsh: command not found: ", 2); //mettre message bash
// 	ft_putstr_fd(pro[0], 2);
// 	ft_putchar_fd('\n', 2);
// 	freetab(pro);
// 	closefd(fd, pipefd1, pipefd2);//, pipefd2);
// 	return (-1);
// }

void    exec(char *buffer,/*, t_envlist *envlist, */char **env)
{
    char    **commandline;
    char    *paths;
    pid_t	p_pid;

    p_pid = fork(); //faire un retour d'erreur si (p_pid < 0)
    if (p_pid == 0)
	{
        commandline = ft_split(buffer, ' '); //securiser le retour du split
        paths = getpath(commandline[0], getmyline(env)/*, pipex*/); //faire une retour d'erreur si !PATH
        execve(paths, commandline, env); //gerer erreur
        freetab(commandline);
        free(paths);
    }
	waitpid (-1, NULL, 0);
}