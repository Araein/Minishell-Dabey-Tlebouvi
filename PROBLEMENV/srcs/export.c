#include "../includes/minishell.h"


/*
si pas de =   -> ne fait rien
doit checker si pas de characteres interdits -> si interdit display une erreur
si =  -> ajoute dans env tout l'argument
si plusieurs =   -> ne prends que a partir du premier

*/
t_envlist *built_in_export(t_envlist *envlist, char *line)
{
    t_envlist   *tempo;
    char        **command;
    char        **test;
    int         i;
    int         j;

    j = 0;
    i = 0;
    tempo = envlist;
    command = ft_split(line, ' ');
    while(command[i])
    {
        test = ft_split(command[i], '=');
        while(test[j])
            j++;
       // printf("J = .%d. command = .%s.\n", j, command[i]);
       printf("commande[i] = .%s.\n", command[i]);
        if(j == 2)
            envlist = ft_add_env(envlist, command[i]);
        //printlist(envlist);
        j = 0;
        i++;
        freetab(test);
    }
    envlist = tempo;
    freetab(command);
    //printlist(envlist);
    return (envlist);
}