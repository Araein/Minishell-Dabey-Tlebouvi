/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:01:32 by dabey             #+#    #+#             */
/*   Updated: 2023/01/25 17:10:51 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	// if (envlist)
	// {
	// 	i = 0;
	// 	while (envlist->line[i + 11] && envlist->line[i + 11] == line[i + 1])
	// 			i++;
	// 	if (i == lenline - 1 && i == whereend(envlist->line) - 11)
	// 			return (envlist);
	// }
	return (NULL);
}

char	*get_env_line_dollar(t_envlist *envlist, char *str_d, int *len)
{
	int			lenline;
	char		*lineresult;

	lineresult = NULL;
	lenline = ft_strlen(str_d); //useless?
	envlist = findline2(envlist, str_d + 1);//pas besoin de malloc line
	if (envlist)
	{
		// printf("****************** = %s\n", envlist->line);
		lineresult = cutline(envlist->line);
		lineresult = removequote(lineresult);
		*len = ft_strlen(lineresult);
		free(str_d);
		str_d = NULL;
		// printf("lineresult = %s\n", lineresult);
	}	
	else
	{
		*len = 0;
		return (NULL);
	}
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
/*fonction qui marche */
char	*ft_new_cmd(char *line, char *str_d, int k, int index)
{
	int		 i;
	int		x;
	int		len_t;
	char	*cmd;
	char	*str_1;

	i = 0;
	x = 0;
	cmd = NULL;
	len_t = ft_strlen(line) + ft_strlen(str_d) - k + 1;
	str_1 = malloc(sizeof(char) * (len_t));
	if (!str_1)
		return (NULL);
	if (line)
	{
		if (index - 1 > 0 )
			str_1 = ft_substr(line, 0, index);// index - 1 ou pas
		cmd = ft_strjoin(str_1, str_d);
		free(str_1);
		free(str_d);
		index += k;
		i = index;
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
/*fonction qui marche */
char    *find_expand_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		j;
	int		k;
	int		db_quote;
	char	*str_d;
	i = 0;
	j = 0;
	k = 0;
	db_quote = 0;
	str_d = NULL;
	if (!line)
		return (NULL);
	while (line[i] != '\0')
	{
		if(line[i] == '\"')
		{
			if (!db_quote)
				db_quote = 1;
			else
				db_quote = 0;
			++i;
		}
		if (line[i] == '\'' && !db_quote)
			i = close_quote(line, ++i);
		else if (line[i] == '\'')
			++i;
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '$')// et si on colle une lettre avant
		{
			if (line[i + 1] == '?')
			{
				str_d = dollar_intero();
				j = i + 2;
				k = 1;
			}
			else
			{
				j = i + 1;
				while (line[j] && line[j] != ' ' && line[j] != '\''
					&& line[j] != '$' && line[j] != '\"')// doit etre ajouter ?? et le '$ '
					j++;
				str_d = ft_substr(line, i, j - i);
				str_d = get_env_line_dollar(envlist, str_d, &k);// ajouter un *len pour la taille de str_d
				// printf("res $_env = %s\n\n", str_d);
			}
			str_d = ft_new_cmd(line, str_d, j - i, i);
			i += k;
			free(line); 
			line = str_d;
		}
		else if (line[i])
			i++;
	}
	return (line);
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
/*
char	*ft_new_cmd(char *line, char *str_d, int k, int index)
{
	int		i;
	int		x;
	int		len_t;
	char	*cmd;
	char	*str_1;

	i = 0;
	x = 0;// 
	cmd = NULL;     // ( 7 + 1 ) - 2 + 1 = 7
	len_t = ft_strlen(line) + ft_strlen(str_d) - k + 1;// a voir
	str_1 = malloc(sizeof(char) * (len_t));// le dollar est il inclus
	if (!str_1)
		return (NULL);
	if (line)
	{
		if (index - 1 > 0 )
			str_1 = ft_substr(line, 0, index);// index - 1 ou pas
		// printf("str_1_avant_$$ = .%s. et inedx = %d et k = %d\n", str_1, index, k);
		// i += k;
		cmd = ft_strjoin(str_1, str_d);
		free(str_1);
		free(str_d);
		// printf("cmd_join__str_avec_$ = %s\n\n",cmd);
		index += k;// 5 + 1 = 6
		i = index;//i = 6
		x = ft_strlen(cmd);// x =  5
			// printf("avant rest x = %d et i = %d et len - 1 = %d\n\n", x,i ,len_t - 1);
		if (x < len_t)
		{
			str_d = ft_strjoin(cmd, line + index);
			free(cmd);
			// printf("passe dans reste = -%s-\n\n", str_d);
			return (str_d);
		}
		// else//a supprimer
		// 	printf("cmd_str_final_$ = %s\n\n",cmd);
	}
	return (cmd);
}
 NOUVELLE METHODE AVEC 3 FONCTION 
char	*find_expand_dollar(t_envlist *envlist, char *line, int *i)
{
	int		j;
	int		k;
	int		index;
	char	*str_d;

	j = 0;
	k = 0;
	index = 0;
	str_d = NULL;
	if (line[*i + 1] == '?')//PROBLEME AVEC $?$?$?
	{
		str_d = dollar_intero();
		j = *i + 2;
		k = 1;
		printf("j_? = %d et k_? = %d et i = %d\n\n", j, k,*i);// i sans $
	}
	else
	{
		j = *i;
		while (line[++j] && line[j] != ' ' && line[j] != '\''
			&& line[j] != '$' && line[j] != '\"')// doit etre ajouter ?? et le '$ '
			j++;
		str_d = ft_substr(line, *i, j - *i);
		printf("str_d$ = %s\n\n",str_d);
		str_d = get_env_line_dollar(envlist, str_d, &k);// ajouter un *len pour la taille de str_d
		printf("NAME_ENV = %s et k = %d\n\n", str_d, k);
	}
	if (str_d)
	{     
		printf("i_new_cmd_3 = %d\n", *i);                   //len $_env_name, i_$
		str_d = ft_new_cmd(line, str_d, j - *i, *i);
		printf("ft_new_cmd = %s\n\n", str_d);
		free(line);
		line = str_d;
	}
	if (k == 0)
		*i += j;
	else
		*i += k;
	free(str_d);
	printf("i de fin de find_expand_$ = %d\n", *i);
	return (line);
}

char	*find_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		db_quote;
	
	i = 0;
	db_quote = 0;
	if (!line)
		return (NULL);
	while (line[i])// echo $? / index = 5 / total = 7
	{
		while(line [i] && line[i] != '$' && line[i] != '\"'
		&& line[i] != '\'')
			i++;
		if(line[i] == '\"')
		{
			if (!db_quote)
				db_quote = 1;
			else
				db_quote = 0;
			++i;
		}
		if (line[i] == '\'' && !db_quote)
			i = close_quote(line, ++i);
		else if (line[i] == '\'')
			++i;
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0')// et si on colle une lettre avant
			line = find_expand_dollar(envlist, line , &i);
		else
			i++;
		printf("line de find_$ = %s\n\n", line);
	}
	return (line);
}
FIND DE FONCTION 3
*/
/*
char	*find_expand_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		j;
	int		k;
	int		db_quote;
	char	*str_d;
	

	i = 0;
	j = 0;
	k = 0;
	db_quote = 0;
	str_d = NULL;
	if (!line)
		return (NULL);
	while (line[i] != '\0')// echo $? / index = 5 / total = 7
	{
		while(line[i] != '$' && line[i] != '\"' && line[i] == '\'')
			i++;
			printf("while_!$ i = %d", i);
		if(line[i] == '\"')
		{
			if (!db_quote)
				db_quote = 1;
			else
				db_quote = 0;
			++i;
		}
		if (line[i] == '\'' && !db_quote)
			i = close_quote(line, ++i);
		else if (line[i] == '\'')
			++i;
		if (line[i] == '$')// et si on colle une lettre avant
		{
			// printf("un passage_if_$ = %d \n\n", i);
			if (line[++i] == '?')//PROBLEME AVEC $?$?$?
			{
				str_d = dollar_intero();
				j = i + 1;
				k = 1;
				printf("j_? = %d et k_? = %d\n\n", j, k);// i sans $
				// str_d = ft_new_cmd(line, str_d, 1, i);// inclure $ ?
				// ++i;
				// printf("str_d$? = %s et i = %d\n\n",str_d, i);// i sans $
			}
			else
			{
				// printf("un passage_else_$ = %d \n\n", i);
				j = i;
				while (line[++j] && line[j] != ' ' && line[j] != '\''
				 && line[j] != '$')//line[j] != '\"' doit etre ajouter ?? et le '$ '
					j++;
				// printf("j = *%d*\n", j);
				str_d = ft_substr(line, i, j - i);
				// printf("str_d$ = %s\n\n",str_d);
				str_d = get_env_line_dollar(envlist, str_d, &k);// ajouter un *len pour la taille de str_d
				printf("NAME_ENV = %s\n\n", str_d);
			}
			if (str_d)
			{     
				printf("i_new_cmd_3 = %d\n", i);                   //len $_env_name, i_$
				str_d = ft_new_cmd(line, str_d, j - i, i);
			}
			i += k;
			printf("i_fin_else_$5 = line[%d]\n", i);
			// printf("res $_final = %s\n\n", str_d);
			free(line);
			line = str_d;
		}
	printf("i++=%d\n", i);
	}
	return (line);
	//fonction entre deux
	}
*/
/*


char	*ft_new_cmd(char *line, char *str_d, int k, int index)
{
	int		i;
	int		x;
	int		len_t;
	char	*str_1;

	i = 0;
	x = 0;
	// printf("x = %d\n\n",x);
	// printf("index = %d\n\n",*index);
	len_t = ft_strlen(line) + ft_strlen(str_d) - k + 1;
	str_1 = malloc(sizeof(char) * (len_t));// le dollar est il inclus
	if (!str_1)
		return (NULL);
	if (line)
	{
		if (index - 1 > 0 )
			str_1 = ft_substr(line, 0, index - 1);// index - 1 ou pas
		// printf("cmd_str_avant_$ = %s.\n\n",str_1);
		// i = *index + k;
		// while (i < index)// et si je test juste index
		// 	str_1[k++] = line[i++];
		// printf("str_1 = %s\n\n",str_1);
		// if (line[i] == '$')
		// {
			// printf("k = %d\n",k);
		printf("index_avant = %d et k = %d\n", index, k);
		printf("index_apes = %d et k = %d\n", index, k);
			// i += k;
		if (str_d)
			str_1 = ft_strjoin(str_1, str_d);
		printf("cmd_join__str_avec_$ = %s\n\n",str_1);
			// while (str_d && str_d[k])// a voir 
			// 	str_1[x++] = str_d[k++];
			// printf("str_2 = %s\n\n",str_1);
			// printf("copie de str_d dans str_1 = %s\n\n",str_1);
			// printf("i = %d et j = %d\n", i,j);
		// }
		// if (ft_strlen(line) > *index)
		// 	str_1 = ft_substr(line, *index, strlen(line + (*index)));
		index += k;
		i = index;
		x = ft_strlen(str_1) - 1;
		while (line[i])
			str_1[x++] = line[i++];
		str_1[x] = '\0';
		printf("cmd_str_final_$ = %s\n\n",str_1);
	}
	free(str_d);
	str_d = str_1;
	return (str_d);
}


char	*find_expand_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*str_d;

	i = 0;
	j = 0;
	str_d = NULL;
	while (line[i])// echo $?$$HOME
	{
		if (line[i] == '\'')
			i = close_quote(line, ++i);
		if (line[i] == '$')// et si on colle une lettre avant
		{
			if (line[i + 1] == ' ')
			{
				str_d = ft_substr(line, i, 1);
				printf("str_d$_ = %s\n\n",str_d);
				k = 1;
				str_d = ft_new_cmd(line, str_d, 1, i);
			}
			else if (line[i + 1] == '?')
			{
				str_d = dollar_intero();
				printf("str_d$? = %s\n\n",str_d);
				k = 2;
				str_d = ft_new_cmd(line, str_d, 2, i);
			}
			else
			{
				j = ++i;
				// printf("k_avant expand= %d et j = %d et i = %d\n\n",k, j , i);
				while (line[j] && line[j] != ' ' && line[j] != '\''
				 && line[j] != '$')//line[j] != '\"' doit etre ajouter ??
					j++;
				// printf("j = %d et i = %d\n\n",j, i);
				str_d = ft_substr(line, i, j);
				printf("str_d$ = %s\n\n",str_d);
				k = j;
					// printf("k_expand= %d et j = %d et i = %d\n\n",k, j , i);
				// i += j;
				// str_d = malloc(sizeof(char) * (j - i + 1));
				// k = 0;
				// while (line[i] && line[i] != ' ' && line[i] != '\"'
				// 	&& line[i] != '\'' && line[j] != '$')
				// 	str_d[k++] = line[i++];
				// str_d[k] = '\0';
				// printf("str_d $ = %s et j = %d\n\n", str_d, j);
				// printf("str_dollar = %s et j = %d\n\n", str_d, j - 1);
				str_d = get_env_line_dollar(envlist ,str_d);
				printf("res $_env = %s\n\n", str_d);
				// if (str_d)
				// {
			str_d = ft_new_cmd(line, str_d, j - i, i);
			 i += j - i - 1;
			}
			printf("res $_final = %s\n\n", str_d);
			// printf("concat de $ = %s\n\n", str_d);
			// printf("line_f = %s + %d\n", str_d, i);
			free(line);
			line = str_d;
			// }
			// else
			// 	line = delete_dollar(line, i, x);
		// else
		// 	i++;
		}
		else
			i++;
	}
	return (line);
}
*/
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

/*
if ' passe a la fin else if " lancer la fonction expand 
- if expand existe dans env change line else i + nb_$name et return (line)
*/