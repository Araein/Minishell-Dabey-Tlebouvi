/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:16:39 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/21 18:50:48 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int		soloarg(char **argv, char **env, t_pipe *pipex)
{
	pid_t	p_pid;
	char	**pro;
	char	*paths;

	p_pid = fork();
	if (p_pid < 0)
	{
		perror("Error");
		return (-1);
	}
	if (p_pid == 0)
	{
		pro = ft_split(argv[1], ' '); //secure
		paths = getpath(pro[0], getmyline(env), pipex);
		if (!paths)
		{
			ft_putstr_fd("zsh: command not found: ", 2); //mettre message bash
			ft_putstr_fd(pro[0], 2);
			ft_putchar_fd('\n', 2);
			freetab(pro);
		}
		execve(paths, pro, env);
		execerror(pro, paths, pipex);
	}
	waitpid (-1, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	pipex;
	int		pipefd[2];

	structinit(&pipex, argc, env, argv);
	if (env[0] == NULL)
	{
		ft_putstr_fd("Error: The environment is not available\n", 2);
		return (-1);
	}
	//creer une fonction si il n'y a pas de pipe a faire (juste exec la commande sans piper)
	if (argc == 2)
		soloarg(argv, env, &pipex);
	else 
	{
		printf("COUCOU\n");
		if (argc == 6 && ft_strcmp(argv[1], "here_doc") == 0)
		{
			if (pipe(pipefd) == -1)
				perror ("Error");
			if (startchildren (pipefd, 1, argv, env) == -1)
				return (-1);
			waitfonc(pipefd, &pipex, 1);
			return (0);
		}
		else
			startchildren2(&pipex, argc);
		waitfonc(pipefd, &pipex, 2); //gerer si il y en a qu'un?
	}
	return (0);
	//DOUBLE FREE EN CAS D'ERREUR AVEC UNE COMMANDE PAS ACCESSIBLE
}



//CREER UN TABLEAU DE PIPE -> STDIN / STDOUT

//SIGPIPE happens normally because you attempt to write to a socket that has
//closed.





/*
ERREURS A REGLER :

Si : valgrind  --leak-check=full --tool=memcheck \
                                --show-reachable=yes \
                                --track-fds=yes \
                                --errors-for-leak-kinds=all \
                                --show-leak-kinds=all \
                                 --trace-children=yes -s ./pipex infile cat cat cadfbt cat /dev/stdout 

==118077== Syscall param close(fd) contains uninitialised byte(s)
==118077==    at 0x4989117: close (close.c:27)
==118077==    by 0x109CA3: closefd (utils_bonus.c:32)
==118077==    by 0x10A0DF: patherror (getpath_bonus.c:92)
==118077==    by 0x10AB44: middlechild (multiple_children_bonus.c:76)
==118077==    by 0x10ADF1: startchildren2 (multiple_children_bonus.c:126)
==118077==    by 0x10940F: main (main_bonus.c:38)

==120396== FILE DESCRIPTORS: 4 open (0 std) at exit.
==120396== Open file descriptor 8:
==120396==    <inherited from parent>
==120396== 
==120396== Open file descriptor 7:
==120396==    <inherited from parent>
==120396== 
==120396== Open file descriptor 6:
==120396==    <inherited from parent>
==120396== 
==120396== Open file descriptor 5:
==120396==    <inherited from parent>

virer ce foutu fd qui reste ouvert tout le temps

RELIER HERE DOC AU PIPEX PRINCIPAL

bien tester le here doc

faire les bons retours avec exit

valgrind ./pipex infile "./directory -c -d" wc /dev/stdout
./pipex infile ./direc wc /dev/stdout
./pipex infile directory wc /dev/stdout
./pipex infile cat wc /bin/cat ls /dev/stdout
./pipex infile cat ww  /dev/stdout
./pipex infile wc ww  /dev/stdout    //SI DEUXIEME COMMANDE EXISTE PAS = BORDEL
./pipex infile cat casgrt cat /dev/stdout
./pipex infile cat wufytc wc /dev/stdout  //probleme de fermeture de fd
./pipex infile cawefwt wc cat /dev/stdout / leak



./pipex infile ./dir1/dir2/dir3 cat /dev/stdout   /DOUBLE FREE ATTENTION
-> pas de soucis si dir1  (sans executable)
GROS LEAK MEME AVEC LE PIPEX DE BASE

Securiser dup2 malloc fd etc....

LS FAIT PETER UN CABLE


pour les 2 fd ouverts ->

./pipex infile sdscat cat cat /dev/stdout   = UN SEULFD ENCORE OUVERT
./pipex infile cat cat cadht /dev/stdout    = UN FD EN PLUS D'OUVERT
*/