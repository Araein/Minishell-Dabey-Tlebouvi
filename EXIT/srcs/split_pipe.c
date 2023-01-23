/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:01:32 by dabey             #+#    #+#             */
/*   Updated: 2023/01/09 13:29:26 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_new_cmd(char *line, char *str_d, int x, int *index)
{
	int		i;
	int		k;
	int		len_t;
	char	*str_1;

	i = 0;
	k = 0;
	// printf("x = %d\n\n",x);
	// printf("index = %d\n\n",*index);
	len_t = ft_strlen(line) + ft_strlen(str_d);
	str_1 = malloc(sizeof(char) * (len_t - x + 1));// le dollar est il inclus
	if (!str_1)
		return (NULL);
	while (line[i])
	{
		while (line[i] && line[i] != '$' && line[i] != '\'')// et si je test juste index
			str_1[k++] = line[i++];
		// printf("str_1 = %s\n\n",str_1);
		if (line[i] == '$')
		{
			*index = i + x;
			i += x;
			x = 0;
			while (str_d && str_d[x])// a voir 
				str_1[k++] = str_d[x++];
			// printf("copie de str_d dans str_1 = %s\n\n",str_1);
			// printf("i = %d et j = %d\n", i,j);
		}
		while (line[i])
			str_1[k++] = line[i++];
		str_1[k] = '\0';
	}
	free(str_d);
	str_d = str_1;
	return (str_d);
}
	// int 	k;
	// char	*str_1;
	// char	*str_2;


	// str_1 = NULL;
	// str_2 = NULL;
	// k = ft_strlen(line);
	// // printf("2\n");
	// // ft_strlen(line + j) ??
	// if (i > 0)
	// 	str_1 = ft_substr(line, 0, --i);//debut de line
	// //printf("substr1 = %s\n", str_1);
	// if (str_1)
	// {
	// 	str_2 = ft_strjoin(str_1, str_d);//debut + expand_dollar
	// 	// printf("strjoin1 = %s\n", str_2);
	// 	free(str_d);
	// 	free(str_1);
	// }
	// if (k - j > 0)
	// 	str_1 = ft_substr(line, j, k);//la fin de line
	// // printf("substr2 = %s\n", str_d);
	// if (str_1)
	// 	str_1 = ft_strjoin(str_2, str_d);//debut + expand_dollar + fin de line
	// // printf("strjoin2 = %s\n", str_1);
	// else
	// 	return (str_d);
	// free(str_2);
	// free(str_d);
	// // free(line);
	// return (str_1);
// }

t_envlist       *findline2(t_envlist *envlist, char *line)
{
	int	i;
	int	lenline;

	if (line == NULL || envlist == NULL)
		return (NULL);
	lenline = ft_strlen(line);
	while (envlist != NULL)
	{
		i = 0;
		while (envlist->line[i] && envlist->line[i + 11] == line[i])
			i++;
		if (i == lenline && i == whereend(envlist->line) - 11)
			return (envlist);
		else
			envlist = envlist->next;
	}
	if (envlist)
	{
		i = 0;
		while (envlist->line[i + 11] && envlist->line[i + 11] == line[i + 1])
				i++;
		if (i == lenline - 1 && i == whereend(envlist->line) - 11)
				return (envlist);
	}
	return (NULL);
}

char	*get_env_line_dollar(t_envlist *envlist, char *str_d)
{
	int			lenline;
	char		*lineresult;

	lineresult = NULL;
	lenline = ft2_strlen(str_d); //useless?
	envlist = findline2(envlist, str_d);//pas besoin de malloc line
	if (envlist)
	{
		lineresult = cutline(envlist->line);
		lineresult = removequote(lineresult);
	}
	// printf("lineresult = %s\n", lineresult);
	free(str_d);
	str_d = NULL;
	return (lineresult);
}

char	first_quote(char *line, int i)
{
	int		j;
	char	first_q;
	
	j = 0;
	while(line[j] && j < i)
	{
		if (line[j] == '\'' || line[j] == '\"')
		{
			if (line[j] == '\'')
				first_q = '\'';
			else
				first_q = '\"';
			j++;
			while (line[j] && j < i && line[j] != first_q)
				j++;
			if (line[j] == first_q)
				first_q = '\0';
			else
				return (first_q);
		}
		j++;
	}
	return ('\0');
}

int		check_dlr_intero(char *line, int i)
{
	if (!line)
		return (0);
	if (line[i] == '?')
	{
		//si ya echo avant $? on imprime sinon erreur
		printf("%d\n", g_status);
		// g_status = 0; la valeur doit elle etre changer ?
		return (1);
	}
	return (0);
}

// char *delete_dollar(char *line, int i,int x)
// {
// 	char	*new_line;

// 	if (!line)
// 		return (NULL);
// 	new_line = NULL;

// 	free(line);
// 	line = new_line;
// 	return (line);
// }

char	*find_expand_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		j;
	int		k;
	int		x;
	char	*str_d;

	i = 0;
	j = 0;
	k = 0;
	x = 0;
	str_d = NULL;
	while (line[i])
	{
		if (line[i] == '\'')
			i = close_quote(line, ++i);
		else if (line[i] == '$')// et si on colle une lettre avant
		{
			// if (i < 0 || ft_isalnum(line[i - 1] == 0)
			if (check_dlr_intero(line, ++i) == 1)
				i++;
			else
			{
				j = i;
				while (line[j] && line[j] != ' ' && line[j] != '\''
				&& line[j] != '\"')
					j++;
				x = j - i + 1;
				str_d = malloc(sizeof(char) * x);
				j = i;
				k = 0;
				while (line[j] && line[j] != ' ' && line[j] != '\"'
					&& line[j] != '\'')
					str_d[k++] = line[j++];
				str_d[k] = '\0';
				// printf("copie du $ = %s et j = %d\n\n", str_d, j);
				// printf("str_dollar = %s et j = %d\n\n", str_d, j - 1);
				str_d = get_env_line_dollar(envlist ,str_d);
				// printf("expon de $ = %s\n\n", str_d);
				// if (str_d)
				// {
					str_d = ft_new_cmd(line, str_d, x, &i);
					// printf("concat de $ = %s\n\n", str_d);
					// printf("str_d_2 = %s\n", str_d);
					free(line);
					line = str_d;
				// }
				// else
				// 	line = delete_dollar(line, i, x);
			}
			// else
			// 	i++;
		}
		else
			i++;
	}
	return (line);
}

char	**expand_dollar(t_envlist *envlist ,char **str_cmd)
{
	int		i;

	if (!str_cmd)
		return (NULL);
	i = 0;
	while (str_cmd[i])
	{
		str_cmd[i] = find_expand_dollar(envlist, str_cmd[i]);
		// printf("str_cmd[%d]=%s.\n\n", i , str_cmd[i]);
		i++;
	}
	return (str_cmd);
}

int	ft_count_word(char *s, char sep)
{
	char	c;
	int		count_w;

	count_w = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			c = *s;
			s++;
			while (*s && *s != c)
				s++;
			if (*s == c)
				s++;
		}
		if (*s == sep)
		{
			s++;
			++count_w;
		}
		while (*s && *s != sep && *s != '\'' && *s != '\"')
			s++;
	}
	// printf("count_w = %d\n", count_w + 1);
	return (++count_w);
}

int	lenght_of_word(char *s, char sep)
{
	int		len_w;
	char	quote_tp;
	
	len_w = 0;
	while (*s && *s != sep)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			len_w++;
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
			{
				s++;
				len_w++;
			}
			s++;
			len_w++;
		}
		else if (*s && *s != sep)
		{
			while (*s && *s != '\'' && *s != '\"' && *s != sep)
			{
				len_w++;
				s++;
			}
		}
	}
	return (len_w);
}

char	**ft_split_pipe(char *buff, char c)
{
	int		i;
	int		j;
	int		count_w;
	char	**tab;
	char	quote_tp;

	i = 0;
	if (!buff)
		return (0);
	count_w = ft_count_word(buff, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		tab[i] = (char *)malloc(sizeof(char) * (lenght_of_word(buff, c) + 1));
		if (!tab[i])
			return (0);
		while (*buff && *buff != c)
		{
			if (*buff && (*buff == '\"' || *buff == '\''))
			{
				quote_tp = *buff;
				tab[i][j++] = *buff++;
				while (*buff && *buff != quote_tp)
					tab[i][j++] = *buff++;
				tab[i][j++] = *buff++;
			}
			while (*buff && *buff != '\"' && *buff != '\'' && *buff != c)
				tab[i][j++] = *buff++;
		}
		tab[i++][j] = '\0';
		if (*buff == c)
			buff++;
	}
	tab[i] = 0;
	return (tab);
}
