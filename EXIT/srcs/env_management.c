#include "../includes/minishell.h"

t_envlist	*ft_new_envnode(char *line, int created)
{
	t_envlist	*new;

	if (line == NULL)
		return (NULL);
	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
		return (NULL);
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
	if (new == NULL)
	{
		if (line)
			free(line);
		return (NULL);
	}
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

void	printlistenv(t_envlist *list)
{
	t_envlist	*tempo;
	int			l;
	char		*tempoline;
	int			equal;

	tempo = list;
	if(!list)                //nouveau
	 	return ;
	while (list != NULL && list->next != NULL)
	{
		if (list->line)
		{
			l = ft_strlen(list->line);
			equal = searchequal(list->line) - 1;// attention au -1 a test
			tempoline = ft_substr(list->line, 11, l - (l - equal) - 9);
			if (tempoline)
			{
				printf("%s", tempoline);
				free(tempoline);
				tempoline = ft_substr(list->line, equal + 3, l - (equal + 4));
				if (tempoline)
				{
					printf("%s", tempoline);
					free(tempoline);
				}
				printf("\n");
			}
		}
		list = list->next;
	}
	if (list != NULL && list->line)
	{
		l = ft_strlen(list->line);
		equal = searchequal(list->line) - 1; //attention au -1 a test
		tempoline = ft_substr(list->line, 11, l - (l - equal) - 9);
		if (tempoline)
		{
			printf("%s", tempoline);
			free(tempoline);
			tempoline = ft_substr(list->line, equal + 3, l - (equal + 4));
			if (tempoline)
			{
				printf("%s", tempoline);
				free(tempoline);
			}
			printf("\n");
		}
	}
	list = tempo;
}

void	printlist(t_envlist *list, int type)
{
	t_envlist	*tempo;

	if (type == 0)
		printlistenv(list);
	else if (list)
	{
		tempo = list;
		while (list != NULL && list->next != NULL)
		{
			if (list->line)
				printf("%s\n", list->line);
			list = list->next;
		}
		if (list != NULL)
			printf("%s\n", list->line);
		list = tempo;
	}
}
//segfault si il n'y a pas d'env a recup attention

// Voilà la liste des variables qui seront ajoutées si elle n’existe pas dans envp :

//     PATH : Pour avoir la liste des dossiers ou chercher les binaires a exécuter
//     HOME : Pour connaitre ou est notre home :D
//     OLDPWD : Pour connaitre le dossier dans lequel nous etions
//     PWD : Pour connaitre le path actuelle
//     SHLVL : Pour savoir combien de shell nous avons lancer

void	change_env_shlvl(char **env, t_envlist *envlist)
{
	char	*string;
	char	*result;
	// char	**tempo;
	// char	*tempoline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	string = "SHLVL=";
	result = NULL;
	while(env[i])
	{
		while(env[i][j])
		{
			if (env[i][j] == string[j])
				j++;
			else
				break ;		
		}
		if (j == 6)
		{
			result = env[i];
			break ;
		}
		j = 0;
		i++;
	}//si on trouve pas -> le creer
	envlist->shlvl_line = NULL;
	if (result)
	{
		string = cutline(result);
		j = ft_atoi(string);
		free(string);
		j++;
		string = ft_itoa(j);
		result = ft_strjoin("SHLVL=", string);
		free(string);
		env[i] = result;
		envlist->shlvl_line = env[i];
	}
	// else
	// {
	// 	tempoline = ft_strjoin("export ", "SHLVL=1");
	// 	tempo = ft_split(tempoline, ' ');
	// 	free (tempoline);
	// 	envlist = built_in_export(envlist, tempo);
	// 	freetab(tempo);
	// 	envlist->shlvl_line = ft_strdup("SHLVL=1"); //ATTENTION
	// 	fprintf(stderr, "\nSHLVLLINE = %s\n", envlist->shlvl_line);
	// }


}

t_envlist	*change_shlvl(t_envlist *envlist, t_list *list, char **env)
{
	char		*line_value;
	char		*joinline;
	t_envlist	*tempo;
	char		**tempotab;
	int			value;

	(void)list;
	change_env_shlvl(env, envlist);
	tempo = envlist;
	envlist = findline(envlist, "$SHLVL");
	if (envlist)
	{
		line_value = cutline(envlist->line);
		line_value = removequote(line_value);
		value = ft_atoi(line_value);
		free(line_value);
		value++;
		line_value = ft_itoa(value);
		joinline = ft_strjoin("export SHLVL=", line_value);// a test
		free(line_value);
		envlist = tempo;
		tempotab = ft_split(joinline, ' ');
		envlist = built_in_export(envlist, tempotab);
		freetab(tempotab);
		free(joinline);
		return (envlist);
	}
	else
	{
		tempotab = ft_split("export SHLVL=1", ' '); // a test
		tempo = built_in_export(tempo, tempotab);
		tempo->shlvl_line = NULL;//ft_strdup("SHLVL=1");
		freetab(tempotab);
	}
	return (tempo);
}

t_envlist	*make_env(char **env, t_list *list)
{
	int			i;
	char		*addquoteline;
	t_envlist	*envlist;

	(void)list;
	i = 0;
	envlist = NULL;
	if (env[i] == NULL)
		return (NULL);
	while (env[i])
	{
		addquoteline = addquote(env[i]);
		envlist = ft_add_env(envlist,
		ft_strjoin("declare -x ", addquoteline), 1);
		free(addquoteline);
		i++;
	}
	envlist = change_shlvl(envlist, list, env);
	// list->envlist = envlist;
	return (envlist);
}


//segfault si il n'y a pas d'env a recup attention

void	free_list_env(t_envlist *list)
{
	t_envlist	*tmp;

	if (list)
	{
		while (list->next != NULL)
		{
			if (list->created == 1)
				free(list->line);
			tmp = list;
			list = list->next;
			free(tmp);
		}
		if (list->created == 1)
			free(list->line);
		free(list);
	}
}


//export yesssssss testencore=oui ===non 64663 non=oui!


/*
To do list :

-gerer l'ajout d'une variable d'env
- Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
qui doivent être substituées par leur contenu.
-env sans aucune option ni argument
-export sans aucune option
-unset sans aucune option
-bash: export: `$=COUCOUCAVABIEN': not a valid identifier
- faire une difference entre env et export (stocker export ailleur??)
-. export une variable vide
- gerer inception de shell?  (execution de ./minishell)
- Creer une fonction qui va chercher et renvoyer une ligne specifique de l'env (pour la modifier ou la supprimer ou l'afficher par ex)

   Unsetting a variable or function that was not previously set
       shall not be considered an error and does not cause the shell to
       abort.


QU'EST CE QUE   _=/usr/bin/env ????
OLDPWD=/mnt/nfs/homes/tlebouvi/PHOENIX/minishell/RECENT


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

export cou"cou=tset"     ->    declare -x coucou="tset"
*/

/*
REMPLACE PAS SI PAS DE =  -> no egal a apas la priorite sur = par contre linverse oui
envoi de caracteres non adaptes

gerer

$$
$?
$!

EXPORT NE MARCHE PAS SI  vide et lance au'un seul mot 
export yes   -> fais rien tant qu'une valeur avec = pas ajoutee
faire unset avec plusieurs arguments
export test
export test=coucou
export test -> cense garder coucocu et pas le remplacer

INVALID READ LORSQUE UNSET 3 VARIABLES (les 3 premieres)

faire env apres avoir unset toute la liste

CHANGER GET ENV LINE POUR QU'IL RETOURNE UN CHAR*
CUTINE VIRE PAS LES ""
rajouter les retour d'erreur pour unset et les autres built in
*/




/*

SHLVL  marche pas
export coucou0 coucou1= couocu2=bonjour   -> s'accumule meme si existe deja

gerer les droits des fichiers 

*/


/*
< test3 ls < test2 cat  << stop

<  1
<< 2
 3
>> 4

char order_and_type -> "112"

char **fd_and_stop ->
fd_and_stop[0] -> test3
fd_and_stop[1] -> test2
fd_and_stop[2] -> stop

charclean_string -> "ls cat"*/



/*
char *leanstring -> commande sans les redirections

char *commande classique -> comnde classique (separee par espaces)
- tester si apres une <, >,>> si apres lui c'est bien un fichier valable 
et si y a rien/dossier/commande/inexistante c'est une erreur 
-
*/


// CHECKER S LES MESSAGES D'ERREUR SONT BIEN SUR LA SORTE D'ERREUR

//  env -i   -> segfault a la fin 
//  faire des tests avec les pipes et export / unset

// gerer overlap de heredoc
// tester comment le code gere les differentes erreurs d'ouverture de file

// securiser le spipes et les fork


/*


Minishell$> cd
Minishell$> pwd
/mnt/nfs/homes/tlebouvi/PHOENIX/minishell/vide
Minishell$> cd
Minishell$> pwd
/mnt/nfs/homes/tlebouvi/PHOENIX/minishell/vide
Minishell$> cd ..
Minishell$> pwd
/mnt/nfs/homes/tlebouvi/PHOENIX/minishell
Minishell$> cd vide/


echo tout seul
GERER LES BUILTIN VIDE

VOIR SI CA FERME BIEN APRES AVOIR UNSET TOUT L'ENVIRONNEMENT



tlebouvi@e2r2p13:~/PHOENIX/minishell/vide$ << stop cat > file1 | < file1 cat
> bonjour
> ca va bien
> stop
bash: file1: No such file or directory

cat: -: input file is output file  (,  < infile cat > infile)







<< stop < infile echo bonjour | < infile echo super > outfile | env > outfile


-> attention ecrit super ET l'env dans outfile au lieu que seulement env


-> gerer commande inexistante seule et au milieu de pipes



changer les heredoc -> appeller tjr le heredoc "here doc"

*/



/*



quand exit est dans des pipes -> ne pas quitter




SI EXIT DANS PIPE FAIRE LE TRUC NORMAL EN LE CONSIDERANT EN BUILTIN
SI PAS DE PIPE -> FAIRE UN CAs PARTICULIER (avant exec?)

*/


/*
verifier avant exec si buffer = 

tlebouvi@e2r7p6:~$ exit 8 | exit 5 54
bash: exit: too many arguments

tlebouvi@e2r7p6:~$ exit regreg
exit
bash: exit: regreg: numeric argument required
e2r7p6%


si dans un pipe -> exit ne quitte pas mais applique le changement de retour d'erreur


*/

//gerer le maximum de fd possible