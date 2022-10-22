/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:47:59 by dabey             #+#    #+#             */
/*   Updated: 2022/10/21 18:19:43 by dabey            ###   ########.fr       */
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

#endif
