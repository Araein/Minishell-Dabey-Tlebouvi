#include "../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*answer;
	int		i;

	i = 0;
	if (!s || len <= 0 || start >= (unsigned int)ft_strlen(s))
		return (NULL);
	answer = malloc(sizeof(char) * len + 1);
	if (answer == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		answer[i] = s[start];
		i++;
		start++;
	}
	answer[i] = '\0';
	return (answer);
}

int	whereend(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=' || line[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

// t_envlist	*findline(t_envlist *envlist, char *line)
// {
// 	int		i;
// 	int		lenline;

// 	if (line == NULL || envlist == NULL)
// 		return (NULL);
// 	lenline = ft_strlen(line);
// 	while (envlist != NULL && envlist->next != NULL)// une condition en moins ??
// 	{
// 		i = 0;
// 		while (envlist->line[i + 11] && envlist->line[i + 11] == line[i])
// 			i++;
// 		if (i == lenline - 1 && i == whereend(envlist->line) - 11)
// 			return (envlist);
// 		else
// 			envlist = envlist->next;
// 	}
// 	if (envlist)
// 	{
// 		i = 0;
// 		while (envlist->line[i + 11] && envlist->line[i + 11] == line[i + 1])
// 			i++;
// 		if (i == lenline - 1 && i == whereend(envlist->line) - 11)
// 			return (envlist);
// 	}
// 	return (NULL);
// }

t_envlist	*findline(t_envlist *envlist, char *line)
{
	int		i;
	int		lenline;

	if (line == NULL || envlist == NULL)
		return (NULL);
	lenline = ft_strlen(line);
	while (envlist != NULL && envlist->next != NULL)
	{
		i = 0;
		while (envlist->line[i + 11] && envlist->line[i + 11] == line[i + 1])
			i++;
		if (i == lenline - 1 && i == whereend(envlist->line) - 11)
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

char	*cutline(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (line == NULL)
		return (NULL);
	while (line[i] && line[i] != '=')
		i++;

	str = ft_substr(line, i + 1 , ft_strlen(line) - (i + 1)); // besoin du + 1?
	return (str);
}
//gerer un retour NULL? renvoyer "" 
//attention retour null probablement pas gere partout

char	*get_env_line(t_envlist *envlist, char *line)
{
	t_envlist	*tempo;
	int			lenline;
	char		*lineresult;

	lineresult = NULL;
	lenline = ft_strlen(line);
	tempo = envlist;
	envlist = findline(envlist, line);
	if (envlist)
	{
		lineresult = cutline(envlist->line);
		// printf("LINERESULT = %s\n", lineresult);
	}
	free(line);
	return (lineresult);
}

char	*removequote(char *line)
{
	char	*tempo;
	int		lenline;

	lenline = ft_strlen(line);
	tempo = line;
	if (lenline > 2)//modifier le >=3
	{
 		line = ft_substr(line, 1, lenline - 2);
		free(tempo);
	}
	return (line);
}
//verifier cas avec plusieurs = ou sans = ?? ou  = des le debut ou des la fin
//segfault si $shell (existe pas)


// NAME=THEO

// je suis $NAME bonjour

// {
//     while (pas $)
//     i++;

// i = 8;

// -> tant ae pas d'espace tu recupere jusqua avoir la variable complete (ici $NAME)

// -> $NAME
// -> THEO

// ------------
// tempo = $NAME;
// buffer = je suis $NAME bonjour
// i = 8;
// variable = THEO

// buffer = join (7 premie char de buffer, variable) -> je suis THEO
// buffer = join (buffer, buffer + strlen(tempo)) -> je suis THEO bonjour

// } --> boucle tant qu'il y a des $ a remplacer dans la commande
