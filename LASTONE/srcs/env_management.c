
#include "../includes/minishell.h"




/*
To do list :

-gerer l'ajout d'une variable d'env
- Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
qui doivent être substituées par leur contenu.
-env sans aucune option ni argument
-export sans aucune option
-unset sans aucune option
-bash: export: `$=COUCOUCAVABIEN': not a valid identifier
- faire une difference entre pwd et export (stocker export ailleur??)
-. export une variable vide
- gerer inception de shell?  (execution de ./minishell)
- Creer une fonction qui va chercher et renvoyer une ligne specifique de l'env (pour la modifier ou la supprimer ou l'afficher par ex)

   Unsetting a variable or function that was not previously set
       shall not be considered an error and does not cause the shell to
       abort.

gerer dollar de dollar
*/

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_envlist	*ft_new_envnode(char *line)
{
	t_envlist	*new;

	//printf("line is = .%s.\n", line);
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
	//printf("Line = .%s.\n", line);
	new = ft_new_envnode(line);
//	printf("newLine = .%s.\n", new->line);
	if (!(list))
		list = new;
	else
	{
		head = list;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
		//printf("lanewlineajoutee est = .%s.\n", head->next->line);
	}
	return (list);
}

void    printlist(t_envlist *list)
{
    t_envlist *tempo;

    tempo = list;
    while(list != NULL && list->next != NULL)
    {
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
//		printf("%s\n", env[i]);
		i++;
	}
  //  printlist(envlist);
    //segfault si il n'y a pas d'env a recup attention
    return (envlist);
}

