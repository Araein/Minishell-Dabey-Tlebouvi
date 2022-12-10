/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:47:59 by dabey             #+#    #+#             */
/*   Updated: 2022/12/09 16:06:52 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// # define couleur(param) printf("\033[%sm",param)

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
	HERDOC_FILE_OUT = 10, //word before <<

}enum_type;

typedef struct envlist
{
    char 			*line;
	int				created;
    struct	envlist *next;
}	t_envlist;

typedef struct s_list
{
	enum_type		type;
	char			*buffer;
	char			**cmd;
	int				buf_size;
	struct s_list	*next;
	int				nb_quote; // = -1 si ya pas et nb si y on a
	int				nb_db_quote; // = -1 si ya pas
	char			*shlvl_line;
}	t_list;



//***********************ft_utils*******************************
t_list		*ft_init(t_list *list);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
void		freetab(char **tab);

//***********************env_management************************
t_envlist	*make_env(char **env, t_list *list);
t_envlist	*ft_add_env(t_envlist *list, char *line, int created);
void  		printlist(t_envlist *list, int type);
void		free_list_env(t_envlist *list);

//***********************export********************************
t_envlist	*built_in_export(t_envlist *envlist, char *line);
char		*addquote(char *line);
int			searchequal(char *line);

//**************************unset******************************
t_envlist   *unset_line(char *buffer, t_envlist *envlist);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strrchr(const char *str, int tsearched);
char		*ft_strndup(const char *str, int n);
int			ft_strlen(const char *s);

//****************************dollars***************************
char		*ft_substr(char const *s, unsigned int start, int len);
t_envlist	*findline(t_envlist *envlist, char *line);
t_envlist	*get_env_line(t_envlist *envlist, char *line);
char		*cutline(char *line);
char		*ft_substr(char const *s, unsigned int start, int len);
int			ft_strncmp(const char *s1, const char *s2, int n);
int			ft_count_w(char const *s, char c);
int			ft_len_w(char const *s, char c);
char		*removequote(char *line);

//**********************command********************************
char		*built_in_pwd();
t_envlist	*built_in_cd(t_envlist *envlist, char *buffer);
char		*ft_strdup(const char *str);

//**********************execution*******************************
void		exec(char *buffer,/* t_envlist *envlist, */char **env);

//**********************itoa**************************************
long long	ft_atoi(const char *str);
char		*ft_itoa(long long n);

//**********************parser***********************
int			check_basic_error(char *buffer);
int			check_quote(char *buffer);
int			parse_quote(char *buffer, t_list *list);

//**********************split_func*****************************
int			ft_count_w(char const *s, char c);
int			ft_len_w(char const *s, char c);
char		**ft_split_quote(char *buffer, char c);

//**********************split_func_utils***********************
int			ft_count_w_simple(char const *s, char c);
int			ft_len_w_simple(char const *s, char c);
// char		**ft_split_space(char *buffer, char c);


#endif
