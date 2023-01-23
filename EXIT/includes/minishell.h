/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:47:59 by dabey             #+#    #+#             */
/*   Updated: 2023/01/23 18:48:22 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// # define couleur(param) printf("\033[%sm",param)
# define STDIN	0 //read
# define STDOUT	1 //write

extern	int		g_status;

typedef	enum	e_type
{
	NONE = 1, // default set
	ARG = 2, // word
	REDI_IN = 3, //word = <
	REDI_OUT = 4, //word = <
	HERDOC_IN = 5, //word = <<
	HERDOC_OUT = 6, //word = >>
	NAME_FILE_IN = 7, //word before <
	NAME_FILE_OUT = 8, //word before >
	HERDOC_STOP = 9, //word before <
	HERDOC_FILE_OUT = 0, //word before <<

}enum_type;

typedef struct envlist
{
    char 			*line;
	int				created;
    struct	envlist *next;
	char			*shlvl_line;
}	t_envlist;

typedef struct s_list
{
	enum_type		type;
	char			*buffer;
	char			**cmd;
	int				buf_size;
	struct s_list	*next;
	int				redirfd[2];
	int				index;
	int				command_count;
	t_envlist		*envlist;
	//////////////redirections///////////////
	char			*clean_string;
	char			**clean_tab;
	char			*to_unlink;
	int				exit;
}	t_list;

//////////////////FONCTION a supprimer////////////////
int	ft2_strlen(const char *s);
int	whereend(char *line);
void printmytab(char **tab);

// ***********************ft_utils*******************************
// t_list		*ft_init(t_list *list);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);

//***********************env_management************************
t_envlist	*make_env(char **env, t_list *list);
t_envlist	*ft_add_env(t_envlist *list, char *line, int created);
void  		printlist(t_envlist *list, int type);
void		free_list_env(t_envlist *list);

// //***********************export********************************
t_envlist	*built_in_export(t_envlist *envlist, char **line);
char		*addquote(char *line);
int			searchequal(char *line);

//**************************unset******************************
t_envlist   *unset_line(char **buffer, t_envlist *envlist, int type);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strrchr(const char *str, int tsearched);
char		*ft_strndup(const char *str, int n);
int			ft_strlen(const char *s);

// //****************************dollars***************************
t_envlist	*findline(t_envlist *envlist, char *line);
char		*get_env_line(t_envlist *envlist, char *line);
char		*cutline(char *line);
char		*ft_substr(char const *s, unsigned int start, int len);
// int			ft_strncmp(const char *s1, const char *s2, int n);
int			ft_count_word(char *s, char c);
int			ft_len_word(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, int n);
// int			ft_count_w(char const *s, char c);
// int			ft_len_w(char const *s, char c);
char		*removequote(char *line);

//**********************command********************************
char		*built_in_pwd();
t_envlist	*built_in_cd(t_envlist *envlist, char **buffer);
char		*ft_strdup(const char *str);

//**********************execution*******************************
int			exec(t_list *list, char **env);
void		close_allpipe(t_list *list, int **pipefd, int type);
void		close_here(t_list *tempo);

//**********************itoa**************************************
long long	ft_atoi(const char *str);
char		*ft_itoa(long long n);

//**********************echo**************************************
int			built_in_echo(char **line);
int 		built_in_exit(t_list *list);


//**********************redirect**************************************
void	dupbonus(t_list *list, int **pipefd, int type);
int		redirect(t_list *list);
void	redirectdup(t_list *list);
int		redirectthis(t_list *list);
int		setup_in(int fd[2], char *to_unlink, char *doc, int type);

//**********************builtin_management*****************************
int checkbuiltin(t_list *list, char **env);

// //**********************parser***********************
int			check_basic_error(char *buffer);
// int			check_quote(char *buffer);
// int			parse_quote(char *buffer, t_list *list);
// // char		*manip_quote_buffer(char *s);

// //**********************split_func***********************

// int			len_word_space(char *s, char sep);
char		**ft_split_pipe(char *buffer, char c);

// //**********************split_pipe***********************
char		**split2(char *s, char c);
char		**expand_dollar(t_envlist *envlist ,char **str_cmd);
// char		*find_expand_dollar(t_envlist *list, char *line);
// int			lenght_of_word(char *s, char sep);
// int			ft_count_word(char *s, char sep);
// char		**ft_split_space(char *s, char c);

// //**********************minishell***********************
void		freetab(char **tab);
void		free_list(t_list *list);


int			close_quote(char *line, int i);


#endif
