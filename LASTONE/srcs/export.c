//#include "../includes/minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct envlist
{
    char 			*line;
    struct	envlist *next;
}	t_envlist;

/*
si pas de =   -> ne fait rien
doit checker si pas de characteres interdits -> si interdit display une erreur
si =  -> ajoute dans env tout l'argument
si plusieurs =   -> ne prends que a partir du premier

*/
static size_t ft_len_w(char const *s, char c)
{
	size_t len_w;

	len_w = 0;
	while (*s != c && *s != '\0')
	{
		len_w++;
		s++;
	}
	return (len_w);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

static size_t ft_count_w(char const *s, char c)
{
	size_t count_w;

	count_w = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			count_w++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (count_w);
}

char **ft_split(char *s, char c)
{
	size_t i;
	size_t j;
	size_t count_w;
	char **tab;

	i = 0;
	if (!s)
		return (NULL);
	count_w = ft_count_w(s, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		while (*s == ' ' || *s == c)
			s++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_len_w(s, c) + 1));
		if (!tab[i])
			return (0);
		while (*s != c && *s != '\0')
		{
			while (*s && *s == ' ' && *(s - 1) == ' ')
				s++;
			tab[i][j++] = *s++;
			while (*s && *s == ' ' && *(s - 1) == ' ')
				s++;
		}
		tab[i++][j] = '\0';
	}
	tab[i] = 0;
	return (tab);
}

t_envlist	*ft_new_envnode(char *line)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
		return (NULL); //proteger
	new->line = line;
	new->next = NULL;
   // printf("lanewlineajoutee est = .%s.\n", new->line);
	return (new);
}

t_envlist	*ft_add_env(t_envlist *list, char *line)
{
	t_envlist	*head;
	t_envlist	*new;

	head = NULL;
	new = ft_new_envnode(line);
	if (!(list))
		list = new;
	else
	{
		head = list;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	return (list);
}

int searchequal(char *line)
{
    int i;

    i = 1;
    while(line[i])
    {
        if(line[i] == '=')  //checker double ==  colle ou non, = a la fin et = au debut
            return (1);     //ajouter verification de char interdits
        i++;
    }
    return (0);
}

t_envlist *built_in_export(t_envlist *envlist, char *line)
{
    char        **variables;
    int         i;

    i = 0;
    variables = ft_split(line, ' ');
    while(variables[i])
    {
        if(searchequal(variables[i]))
            envlist = ft_add_env(envlist, variables[i]);
    //  free(variables[i]);
        i++;
    }
//    free(variables[1]);
    free(variables);
    //freetab(variables);
    return (envlist);
}

void    printlist(t_envlist *list)
{
    t_envlist *tempo;

    tempo = list;
    while(list != NULL && list->next != NULL)
    {
        if(list->line)
            printf("%s\n", list->line);
        list = list->next;
    }
	if (list != NULL)
    	printf("%s\n", list->line);
    list = tempo;
        //segfault si il n'y a pas d'env a recup attention
}

t_envlist *make_env(char **env)
{
	int	i;
    t_envlist   *envlist;

	i = 0;
    envlist = NULL;

	while (env[i])
	{
        envlist = ft_add_env(envlist, env[i]);
		i++;
	}
    //segfault si il n'y a pas d'env a recup attention
    return (envlist);
}


/*

dans envlist :
line->env  = ne sont pas a free car viennent directement de env
mais les nouvelles qui sont ajoutees sont malloc, elles sont donc a free
*/
void	free_list(t_envlist *list)
{
	t_envlist	*tmp;

	tmp = list;
	//free(tmp->line);
	while (list != NULL)
	{
  //      free(tmp->line);
		tmp = list;
		list = list->next;
		free(tmp);
		// tmp = list;
	}
}

int main(int argc, char **argv, char **env)
{
    t_envlist   *envlist;
    int         i;

    i = 0;
    envlist = make_env(env);

    printf("l'environnement est :\n\n\n");
    while(argv[i + 1])
    {
        envlist = built_in_export(envlist, argv[i + 1]);
        i++;
    }
    printlist(envlist);
    printf("\n\n\n");
    free_list(envlist);
    return (0);
}