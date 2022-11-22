#include "../includes/minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *str, int tsearched)
{
	int		i;
	char	searched;

	searched = (char)tsearched;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[ft_strlen(str) - i] == searched)
			return ((char *)&str[ft_strlen(str) - i]);
		i++;
	}
	if (str[ft_strlen(str) - i] == searched)
		return ((char *)&str[ft_strlen(str) - i]);
	return (0);
}
///FAIRE ATTENTION A BIEN TESTER TOUS LES CAS

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	p;

	l = ft_strlen(s1);
	p = ft_strlen(s2);
	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * ((l + p + 1)));
	if (!dest)
		return (NULL);
	while (++i < l)
	{
		dest[i] = s1[i];
	}
	while (++j < p)
	{
		dest[i] = s2[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
//implementer la possibilite d'unset plusieurs variables d'un coup !!!!

t_envlist	*unset_line(char *buffer, t_envlist *envlist)
{
	char		*tempo;
	t_envlist	*tempolist;
	t_envlist	*goodlist;
	t_envlist	*firstlist;

	firstlist = envlist;
	tempo = ft_strjoin ("$", buffer);
	goodlist = findline(envlist, tempo);
	free(buffer);
	free(tempo);
	if (goodlist == NULL)
		return (firstlist);
	if (envlist == goodlist)
	{
		tempolist = envlist;
		if (envlist->created == 1)
			free(envlist->line);
		envlist = envlist->next;
		free(tempolist);
		return (envlist);
	}
	while (envlist->next && envlist->next != goodlist)
		envlist = envlist->next;
	if (envlist->next == goodlist)
	{
		tempolist = envlist->next;
		if (envlist->next->created == 1)
			free(envlist->next->line);
		envlist->next = envlist->next->next;
		free(tempolist);
		return (firstlist);
	}
	return (firstlist);
}
