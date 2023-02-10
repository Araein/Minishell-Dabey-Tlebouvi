/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:38:05 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 21:04:21 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	close_quote(char *line, int i)
{
	while (line[i])
	{
		if (line[i] && line[i] != '\'')
			i++;
		else
			return (++i);
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

void	pipe_quote(char *buffer, int *i)
{
	char	quote_tp;

	if (buffer[*i] && (buffer[*i] == '\"' || buffer[*i] == '\''))
	{
		quote_tp = buffer[*i];
		(*i)++;
		while (buffer[*i] && buffer[*i] != quote_tp)
			(*i)++;
		if (buffer[*i] && buffer[*i] == quote_tp)
			(*i)++;
	}
}

int	error_pipe(char *buffer)
{
	int		i;
	int		nb_pipe;

	i = 0;
	if (buffer && buffer[i] && (buffer[i] == '|'
			|| ((buffer[ft_strlen(buffer) - 1]) == '|')))
		return (0);
	while (buffer[i])
	{
		pipe_quote(buffer, &i);
		while (buffer[i] && buffer[i] != '|' && buffer[i] != '\''
			&& buffer[i] != '\"')
			i++;
		nb_pipe = 0;
		while (buffer[i] && (buffer[i] == '|' || buffer[i] == ' '))
		{
			if (buffer[i] == '|')
				++nb_pipe;
			if (nb_pipe > 1)
				return (0);
			i++;
		}
	}
	return (1);
}

int	check_basic_error(char *buffer)
{
	if (check_quote(buffer) != 0)
	{
		printf("error : quote not close\n");
		return (0);
	}
	else if (error_pipe(buffer) != 1)
	{
		printf("bash : syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}
