#include "../includes/minishell.h"



char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	p;
	
	l = ft_strlen(s1);
	p = ft_strlen(s2);
	i = 0;
	j = 0;
	if (!(dest = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (NULL);
	while (i < l)
	{
		dest[i] = s1[i];
		i++;
	}
	while (j < p)
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

t_envlist    *unset_line(char *buffer,t_envlist *envlist)
{
    char        *line;
    t_envlist   *tempolist;
    t_envlist   *goodlist;
    t_envlist   *firstlist;

    firstlist = envlist;

    line = ft_substr(buffer, 6, ft_strlen(buffer) - 5); //attention a free
    goodlist = findline(envlist, ft_strjoin ("$", line)); //join leak?
    free(line);
    if(goodlist == NULL)
        return(firstlist);
    if(envlist == goodlist)
    {
        tempolist = envlist;
       // free(envlist->line);
        envlist = envlist->next;
        free(tempolist);  //tricky
        return (envlist);
    }
    while(envlist->next && envlist->next != goodlist)
        envlist = envlist->next;
    if(envlist->next == goodlist)
    {
        tempolist = envlist->next;
    //  free(envlist->line);
        envlist->next = envlist->next->next;
        free(tempolist);  //tricky
        return (firstlist);
    }
    return(firstlist);

    //gerer les specificites de unset (variable vides par ex)
}
