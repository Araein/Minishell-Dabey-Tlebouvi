/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:16:43 by tlebouvi          #+#    #+#             */
/*   Updated: 2022/10/17 18:26:37 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_pipe
{
	char	**argv;
	char	**env;
	int		program;
	int		argc;
	int		type;
	int		index;
	int		islink;
	int		iserr;
	int		fd[2];
}				t_pipe;

char	*getmyline(char **env);
char	*getpath(char *pro, char *goodline,  t_pipe *pipex);
int		main(int argc, char **argv, char **env);
int		ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_putstr_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	**getpath_bonus(char *pro, char *goodline);
void	freetab(char **tab);
int		firstchild(int pipefd[2], int fd[2], char **argv, char **env);
int		secondchild(int pipefd[2], int fd[2], char **argv, char **env);
void	closefd(int one, int two, int three);
int		patherror(char **pro, int fd, int pipefd1, int pipefd2);
int		patherrormid(char **pro, int pipefd1, int pipefd2);
char	*minifreetab(char **tab, char *result);
int		errorpid(int pipefd[2]);
int		openfd(char	*argv, int fd[2], int type, int pipefd[2]);
int		dupfonc(int pipefd[2], int fd[2], int type);
int		checkpro(char *pro);
void	typefd(int type, int fd[2], char *argv);
void	dealwitherror(char **pro, char *paths);
void	readfunc(int *u, char **argv, int fd[2]);
int		setuphere(char **argv, int fd[2]);
int		secondherechild(int pipefd[2], int fd[2], char **argv, char **env);
int		firstherechild(int pipefd[2], int fd[2], char **argv, char **env);
int		writefunc(int fd[2], char *argv, int j, char content);
int		ft_strcmp(const char *s1, const char *s2);
int		writefunc(int fd[2], char *argv, int j, char content);
int		errorpid(int pipefd[2]);
void	execerror(char **pro, char *paths, t_pipe *pipex);
int		errorfd(int pipefd[2], t_pipe *pipex, int type);
int		startchildren2(t_pipe *pipex, int argc);
int		startchildren(int pipefd[2], int type, char **argv, char **env);
void	freeandclose(t_pipe *pipex, int **pipefd, int argc, int type);
int		**mallocandpipe(int argc, t_pipe *pipex);
void	dupbonus(t_pipe *pipex, int pipefd[2], int pipeout[2], int type);
void	structinit(t_pipe *pipex, int argc, char **env, char **argv);
void	waitfonc(int pipefd[2], t_pipe *pipex, int type);

#endif
