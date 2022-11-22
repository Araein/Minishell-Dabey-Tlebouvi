#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	p;

	l = ft_strlen(s1);
	p = ft_strlen(s2);
	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * ((l + p + 1)));
	if (!dest)
		return (NULL);
	while (++i < l)
	{
		dest[i] = s1[i];
	}
	while (++j < p)
	{
		dest[i] = s2[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		lineisn(char *line)
{
	int	i;

	i = 1;
	if (line[0] != '-')
		return (0);
	while (line[i])
	{
		if (line[i] != 'n')
			return (0);
		else
			i++;
	}
	return (1);
}

int		checkn(char **line)
{
	int	i;

	i = 1;
	while (lineisn(line[i]) == 1)
		i++;
	return (i - 1);
}

void    built_in_echo(char **line, int linelength)
{
    int     i;
    char    *join;
    int     oops; // a enlever
	int		check;

    oops = 0; //a enlever
    i = 0;
	check = checkn(line);
    if (check > 0)
        i += check;
    else
    {
        join = line[linelength - 1];
       // free(line[linelength - 1]);
        line[linelength - 1] = ft_strjoin(join, "\n"); //securiser ce malloc
       // free(join);
       oops = 1; // a enlever
    }
    while (i < linelength - 1)
    {
        if (i == linelength - 2)
            printf("%s", line[i + 1]);
        else
            printf("%s ", line[i + 1]);
        i++;
    }
    if(oops == 1)
        free(line[linelength - 1]); //free tab normalement
}

void    built_in_pwd()
{
    char    buffer[FILENAME_MAX];  //marche si on supprime env?? 

    if (getcwd(buffer, sizeof(buffer)) != NULL) 
	       printf("%s\n", buffer); //free? 
	else
	    perror("getcwd()"); //voir les retours d'erreur
}

void    built_in_exit()
{
	//printf exit
	    exit(EXIT_SUCCESS); //voir les retours d'erreur d'Exit etc...                                                                                                                                                                                                                                                                                                         
	
}

int main (int argc, char **argv)
{
    if (ft_strcmp(argv[1], "pwd") == 0)
        built_in_pwd();
    else if (ft_strcmp(argv[1], "exit") == 0)
        built_in_exit();
    else
        built_in_echo(argv, argc);
//    printf("TESt\n");
    return (0);
}


#include "../includes/minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	p;

	l = ft_strlen(s1);
	p = ft_strlen(s2);
	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * ((l + p + 1)));
	if (!dest)
		return (NULL);
	while (++i < l)
	{
		dest[i] = s1[i];
	}
	while (++j < p)
	{
		dest[i] = s2[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		lineisn(char *line)
{
	int	i;

	i = 1;
	if(line[0] != '-')
		return (0);
	while(line[i])
	{
		if(line[i] != 'n')
			return (0);
		else
			i++;
	}
	return (1);
}

int		checkn(char **line)
{
	int	i;

	i = 1;
	while(lineisn(line[i]) == 1)
		i++;
	return (i - 1);
}



void    built_in_echo(char **line, int linelength /*nombre de strings dans line*/)
{
    int     i;
    char    *join;
    int     oops; // a enlever
	int		check;

    oops = 0; //a enlever
    i = 0;
	check = checkn(line);
    if (check > 0)
        i += check;
    else
    {
        join = line[linelength - 1];
       // free(line[linelength - 1]);
        line[linelength - 1] = ft_strjoin(join, "\n"); //securiser ce malloc
       // free(join);
       oops = 1; // a enlever
    }
    while (i < linelength - 1)
    {
        if (i == linelength - 2)
            printf("%s", line[i + 1]);
        else
            printf("%s ", line[i + 1]);
        i++;
    }
    if(oops == 1)
        free(line[linelength - 1]); //free tab normalement
}

void    built_in_pwd()
{
    char    buffer[FILENAME_MAX];  //marche si on supprime env?? 

    if (getcwd(buffer, sizeof(buffer)) != NULL) 
	       printf("%s\n", buffer); //free? 
	else
	    perror("getcwd()"); //voir les retours d'erreur

		/*gerer l'environnement*/
}

void    built_in_exit()
{
	//printf exit
	    exit(EXIT_SUCCESS); //voir les retours d'erreur d'Exit etc...                                                                                                                                                                                                                                                                                                         
	
}

int main (int argc, char **argv)
{
    if (ft_strcmp(argv[1], "pwd") == 0)
        built_in_pwd();
    else if (ft_strcmp(argv[1], "exit") == 0)
        built_in_exit();
    else
        built_in_echo(argv, argc);
    return (0);
}

