#include "../includes/minishell.h"

char    *built_in_pwd()
{
    char    *buffer;  //marche si on supprime env?? 
    size_t allocsize;
    
    allocsize = sizeof(char) * FILENAME_MAX;
	buffer = (char *)malloc(sizeof(char) * allocsize);
    if (buffer == NULL)
        return (NULL);
    if (getcwd(buffer, allocsize) != NULL)
    {
    }
	else
	    perror("getcwd()"); //voir les retours d'erreur
    return (buffer);
}

//gerer cd avec plusieurs arguments ????? "uniauement un chemin"
//   Comportement bizarre : echo coucou > BONJOUR | pwd test | echo yo
char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen((char *)str) + 1))))
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_envlist   *built_in_cd(t_envlist *envlist, char **buffer)
{
    char        *oldpwd;
    char        *tempo2;
    char        *tempo;
    char        **tempotab;
    t_envlist   *tempolist;
    int         i;

    i = 0;
    while(buffer[i])
        i++;
    if (i == 1)
        return (envlist);//retour d'erreur?
    if (i != 2)
    {
        write(2,"bash: cd: too many arguments\n", 29);
        g_status = 1;
        return (envlist);
    }

	if (chdir(buffer[1]) == 0)
    {
        tempolist = findline(envlist, "$PWD");
        if(tempolist)
        {
            oldpwd = cutline(tempolist->line);
            oldpwd = removequote(oldpwd);
        }
        else
            oldpwd = NULL;
        tempo =  built_in_pwd();
        tempo2 = ft_strjoin("cut PWD=", tempo); //a test
        //a modifier plus tard (enlever le t quand le i de export sera a 0)
        tempotab = ft_split(tempo2, ' ');
        envlist = built_in_export(envlist, tempotab);
        freetab(tempotab);
        free (tempo);
        free (tempo2);
        tempo = NULL;
        tempo2 = NULL;
        if (oldpwd)
        {
            tempo = oldpwd;
            tempo2 = ft_strjoin("cut OLDPWD=", tempo);
            tempotab = ft_split(tempo2, ' ');
        //a modifier plus tard (enlever le t quand le i de export sera a 0)
            envlist = built_in_export(envlist, tempotab); // a test
            freetab(tempotab);
            free (tempo);
            free (tempo2);
        }
        g_status = 0;
    }
    else
	{
        tempo = ft_strjoin("bash: cd: ", buffer[1]);
        perror(tempo);
        free(tempo);
        g_status = 1;
    }
    return (envlist);
}
//FAIRE EN SORTE QU PW LISE DEPUI L'ANCIEN PWD