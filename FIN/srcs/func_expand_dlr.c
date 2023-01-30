/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_expand_dlr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:52:08 by dabey             #+#    #+#             */
/*   Updated: 2023/01/30 20:52:24 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dollar_intero(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str = ft_itoa(g_status);
	g_status = 0;
	return (str);
}

int	init_new_cmd(char **str_1, char **cmd, int *x, int *len_t)
{
	*x = 0;
	*cmd = NULL;
	*str_1 = malloc(sizeof(char) * (*len_t));
	if (!*str_1)
		return (0);
	return (1);
}

char	*ft_new_cmd(char *line, char *str_d, int k, int index)
{
	int		x;
	int		len_t;
	char	*cmd;
	char	*str_1;

	len_t = ft_strlen(line) + ft_strlen(str_d) - k + 1;
	if (!init_new_cmd(&str_1, &cmd, &x, &len_t))
		return (NULL);
	if (line)
	{
		if (index - 1 > 0)
			str_1 = ft_substr(line, 0, index);
		cmd = ft_strjoin(str_1, str_d);
		free(str_1);
		free(str_d);
		index += k;
		x = ft_strlen(cmd);
		if (x < len_t)
		{
			str_d = ft_strjoin(cmd, line + index);
			free(cmd);
			return (str_d);
		}
	}
	return (cmd);
}

void	expand_quote(char *line, int *i)
{
	char	db_quote;

	db_quote = 0;
	if (line[*i] == '\"')
	{
		if (!db_quote)
			db_quote = 1;
		else
			db_quote = 0;
		++(*i);
	}
	if (line[*i] == '\'' && !db_quote)
		*i = close_quote(line, ++(*i));
	else if (line[*i] == '\'')
		++(*i);
}

char	*funct_dollar_intero(char *str_d, int *i, int *j, int *k)
{
	str_d = dollar_intero();
	*j = *i + 2;
	*k = 1;
	return (str_d);
}
