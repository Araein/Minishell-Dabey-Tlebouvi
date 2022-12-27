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

t_envlist   *built_in_cd(t_envlist *envlist, char *buffer)
{
    char        *arg;
    char        *oldpwd;
    char        *tempo2;
    char        *tempo;
    t_envlist   *tempolist;

    arg = ft_substr(buffer, 3, ft_strlen(buffer) - 3); //a free 
	if (arg == NULL)
		return (0);
	if (chdir(arg) == 0)
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
        tempo2 = ft_strjoin("t PWD=", tempo); 
        //a modifier plus tard (enlever le t quand le i de export sera a 0)
        envlist = built_in_export(envlist, tempo2);
        free (tempo);
        free (tempo2);
        tempo = NULL;
        tempo2 = NULL;
        if (oldpwd)
        {
            tempo = oldpwd;
            tempo2 = ft_strjoin("t OLDPWD=", tempo); 
        //a modifier plus tard (enlever le t quand le i de export sera a 0)
            envlist = built_in_export(envlist, tempo2);
            free (tempo);
            free (tempo2);
        }
        g_status = 0;
    }
    else
	{
        tempo = ft_strjoin("bash: cd: ", arg);
        perror(tempo);
        g_status = 1;
        free(tempo);
    }
    free(arg);
    return (envlist);
}

//permission denied
//too many arguments a gerer !!!
//no such file or directory
//target is not a diretory
