/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:38:05 by dabey             #+#    #+#             */
/*   Updated: 2023/01/20 22:09:08 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*simplify_cmd(char *buffer)//echo  bon"jour" 'to'to si y a deja espace on supprime l'espace d'apres
// {
// 	int		i;
// 	char	c;
// 	int		begin_str;

// 	i = 0;
// 	begin_str = 0;
// 	if (!buffer)
// 		return (NULL);
// 	while (buffer[i])
// 	{
// 		while (buffer[i] && buffer[i] != '\'' && buffer[i] != '\'')
// 			i++;
// 		if (buffer[i] && buffer[i] == '\'')
// 		{
// 			c = buffer[i];
// 			if (is_not_separator(buffer, i))
// 			{
// 				ft_substr(buffer, i + 1, )
// 				strlen_type(buffer, i, c)
// 			}
// 		}
// 	}
// }

int	close_quote(char *line, int i)
{
	while (line[i])
	{
		if (line[i] && line[i] != '\'')
			i++;
		else
			return(++i);
	}
	return (-1);
}

int	check_quote(char *buffer)
{
	int		i;
	int		quote;
	char	c;

	i = 0;
	quote = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\'' || buffer[i] == '\"')
		{
			c = buffer[i];
			++quote;
			i++;
			while (buffer[i] && buffer[i] != c)
				i++;
			if (buffer[i] == c)
				--quote;
		}
		if (quote != 0)
			return (quote);
		i++;
	}
	return (quote);
}

int	error_pipe(char *buffer)
{
	int		i;
	int		nb_pipe;
	char	quote_tp;

	i = 0;
	nb_pipe = 0;
	if (buffer && buffer[i] && (buffer[i] == '|' || ((buffer[ft_strlen(buffer) - 1])
	 == '|')))
		return (0);
	while (buffer[i])
	{
		if (buffer[i] && (buffer[i] == '\"' || buffer[i] == '\''))
		{
			quote_tp = buffer[i];
			i++;
			while (buffer[i] && buffer[i] != quote_tp)
				i++;
			if (buffer[i] && buffer[i] == quote_tp)
				i++;
		}
		while (buffer[i] && buffer[i] != '|' && buffer[i] != '\''
		 && buffer[i] != '\"')
			i++;
		while (buffer[i] && (buffer[i] == '|' || buffer[i] == ' '))
		{
			if (buffer[i] == '|')
				++nb_pipe;
			if (nb_pipe > 1)
				return (0);
			i++;
		}
		nb_pipe = 0;
	}
	return (1);
}

// int	check_redir(char * buffer)
// {
// 	int i;

// 	i = 0;
// 	while (buffer[i])
// 	{
// 		if (buffer[i] == '>')
// 	}
// }

int	check_basic_error(char *buffer)
{
	// if (check_redir(buffer) != 0)
	// {
	// 	printf("bash: syntax error near unexpected token `>'\n");
	// 	return (0);
	// }
	if (check_quote(buffer) != 0)
	{
		printf("error : quote not close\n");
		return (0);
	}
	else if (error_pipe(buffer) != 1) // checker le pipe entre des espace ' espace | espace'
	{
		printf("bash : syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

/*
char	**ft_split_quote(char *buffer, char c)
{
	int		i;
	int		j;
	char	**tab;
	int		count_w;
	// size_t	is_quote;

	i = 0;
	if (!buffer)
		return (0);
	count_w = ft_count_w(buffer, '|');
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*buffer == ' ' || *buffer == c)
			buffer++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w(buffer, ' ') + 1));
		if (!tab[i])
			return (0);
		while (*buffer != c && *buffer != '\0')
		{
			while (*buffer && *buffer == ' ' && *(buffer - 1) == ' ')
				buffer++;
			tab[i][j++] = *buffer++;
			while (*buffer && *buffer == ' ' && *(buffer- 1) == ' ')
				buffer++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
/////////////////////////////////////
int ft_count_w(char const *s, char c)
{
	int	quote;
	int	booll;
	int	count_w;

	booll = 0;
	quote = 0;
	count_w = 0;
	while (*s)
	{
		if (*s == '\"')
		{
			s++;
			while (*s && *s != '\"')// erreur probable
				s++;
			if (*s != '\"')
			{
				s++;
				count_w++;
				printf("**count_word0 = %d**\n", count_w);
				printf ("test0 = %s\n\n", s);
			}
		}
		if (*s && *s == '\'')//else
		{
			s++;
			while (*s && *s != '\'')
				s++;
			if (*s && *s != '\'')
			{
				s++;
				count_w++;
				printf("**count_word1 = %d**\n", count_w);
				printf ("test1 = %s\n\n", s);
			}
		}
		if (*s && (*s == c || *s == ' '))
			s++;
		while (*s && *s <65 && *s <= 99 && *s != '\"')
		{
			booll = 1;
			s++;
		}
		if (*s && booll)
		{
			booll = 0;
			count_w++;
			printf("**count_word2 = %d**\n", count_w);
			s++;
			printf ("test2 = %s\n\n", s);
		}
	}
	return (count_w);
}
*/