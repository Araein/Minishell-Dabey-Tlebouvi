/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:47:59 by dabey             #+#    #+#             */
/*   Updated: 2022/11/03 18:02:03 by tlebouvi         ###   ########.fr       */
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

//***********************ft_uils********************
t_list	*ft_init(t_list *list);
char	**ft_split(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	freetab(char **tab);
//***********************env************************
t_envlist	*make_env(char **env);
t_envlist	*ft_add_env(t_envlist *list, char *line);
t_envlist	*ft_new_envnode(char *line);
void  		printlist(t_envlist *list);
//***********************export*********************
t_envlist *built_in_export(t_envlist *envlist, char *line);



char	**mysplit(char const *s, char c);


#endif
