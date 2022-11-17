/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:47:59 by dabey             #+#    #+#             */
/*   Updated: 2022/11/17 15:04:31 by tlebouvi         ###   ########.fr       */
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

typedef	enum	e_type
{
	WORD = 1,
	QUATE = 2,
	COMMANDE = 3,
	ARG = 4,
	OPTION = 5,
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
	size_t			buf_size;
	struct s_list	*next;
	int				nb_quate; // = -1 si ya pas et nb si y on a
	int				nb_db_quate; // = -1 si ya pas 
}	t_list;

//***********************ft_utils*******************************
t_list		*ft_init(t_list *list);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
void		freetab(char **tab);

//***********************env_management************************
t_envlist	*make_env(char **env, int type);
t_envlist	*ft_add_env(t_envlist *list, char *line, int created);
void  		printlist(t_envlist *list);
void		free_list_env(t_envlist *list);

//***********************export********************************
t_envlist	*built_in_export(t_envlist *envlist, char *line, int type);
char		*addquote(char *line);
int			searchequal(char *line);

//**************************unset******************************
t_envlist   *unset_line(char *buffer,t_envlist *envlist, int type);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strrchr(const char *str, int tsearched);
char		*ft_strndup(const char *str, int n);
int			ft_strlen(const char *s);

//****************************dollars***************************
char		*ft_substr(char const *s, unsigned int start, int len);
t_envlist	*findline(t_envlist *envlist, char *line, int type);
t_envlist	*get_env_line(t_envlist *envlist, char *line);
char		*cutline(char *line);
char		*ft_substr(char const *s, unsigned int start, int len);
int			ft_strncmp(const char *s1, const char *s2, int n);

// static size_t	ft_count_w(char const *s, char c);
// static size_t	ft_len_w(char const *s, char c);

//**********************parser***********************
int				check_quote(char *buffer);
int				parse_quote(char *buffer, t_list *list);

#endif
