#include "../includes/minishell.h"


int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_envlist	*ft_new_envnode(char *line, int created)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
		return (NULL); //proteger
	new->line = line;
	new->created = created;
	new->next = NULL;
   // printf("lanewlineajoutee est = .%s.\n", new->line);
	return (new);
}

t_envlist	*ft_add_env(t_envlist *list, char *line, int created)
{
	t_envlist	*head;
	t_envlist	*new;

	head = NULL;
	new = ft_new_envnode(line, created);
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
            envlist = ft_add_env(envlist, variables[i], 1);
		else
			free(variables[i]); //on free variables qui ne seront pas add a env
        i++;
    }
    free(variables);
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
	t_envlist	*tempo;

	i = 0;
    envlist = NULL;
	while (env[i])
	{
        envlist = ft_add_env(envlist, env[i], 0);
		i++;
	}
	tempo = envlist;
    //segfault si il n'y a pas d'env a recup attention
    return (tempo);
}


void	free_list_env(t_envlist *list)
{
	t_envlist	*tmp;

	while (list->next != NULL)
	{
		if(list->created == 1)
			free(list->line);
		tmp = list;
		list = list->next;
		free(tmp);
	//	tmp = list;
	}
	if(list->created == 1)
		free(list->line);
	free(list);
}