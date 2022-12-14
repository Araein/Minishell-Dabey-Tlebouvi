
#include "../includes/minishell.h"

t_envlist	*ft_new_envnode(char *line, int created)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
		return (NULL); //proteger
	new->line = line;
	new->created = created;
	new->next = NULL;
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

t_envlist *make_env(char **env, int type)
{
	int	i;
    char		*addquoteline;
	t_envlist   *envlist;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		if (type == 0)
        	envlist = ft_add_env(envlist, env[i], 0);
		else
		{
			addquoteline = addquote(env[i]);
			envlist = ft_add_env(envlist, ft_strjoin("declare -x ", addquoteline), 1);   //gerer si le join retourne NULL
			free(addquoteline);
		}
		i++;
	}
    //segfault si il n'y a pas d'env a recup attention
    return (envlist);
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
	}
	if(list->created == 1)
		free(list->line);
	free(list);
}

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
declare -x TEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEST="" --> mettre qqch quand meme dedans
declare -x TEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEST2="="

si tu met pas de = -> ca va dans export mais pas dans env  -> voir apres comment ca evolue/est remplace
faire des test en les supprimant ou ajoutant
faire encore une autre lite chainee pour export? 
faire un join "declare -x " sur toutes les commandes de env
-> toutes les lines seront donc malloc dans export
"
attention mettre egalement apre le = "" !!!!!
*/

/*
REMPLACE PAS SI PAS DE =  -> no egal a apas la priorite sur = par contre linverse oui
envoi de caracteres non adaptes

gerer

$$
$?
$!


*/
