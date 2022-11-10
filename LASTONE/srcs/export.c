#include "../includes/minishell.h"


/*
si pas de =   -> ne fait rien
doit checker si pas de characteres interdits -> si interdit display une erreur
si =  -> ajoute dans env tout l'argument
si plusieurs =   -> ne prends que a partir du premier

*/

int searchequal(char *line)
{
    int i;

    i = 1;
  //  printf("lines dans searchequal = %s\n", line);
    while(line[i])
    {
        if(line[i] == '=')  //checker double ==  colle ou non, = a la fin et = au debut
            return (1);
        i++;
    }
  //  printf("lines error dans searchequal = %s\n", line);
    return (0);
}

t_envlist *built_in_export(t_envlist *envlist, char *line)
{
    char        **variables;
    int         i;

    i = 1;
    variables = ft_split(line, ' ');
    while(variables[i])
    {
        if(searchequal(variables[i]))
            envlist = ft_add_env(envlist, variables[i]);
        i++;
    }
    freetab(variables);
    return (envlist);
}