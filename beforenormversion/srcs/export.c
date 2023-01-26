#include "../includes/minishell.h"

int	searchequal(char *line)
{
	int	i;

    i = 1;
	while (line[i])
	{
		if (line[i] == '=')
			return (i); //ATTENTION AVANT C'ETAIT  i - 1
		i++;
	}
	return (0);
}

int	checkvariable(char *line) //gerer les $?
{
	int	i;

	i = 0;

	if (line[i] != '_' && (line[i] < 65 || line[i] > 90)
		&& (line[i] < 97 || line[i] > 122))
		return (1);

	return (0);
}

// TESTER VARIABLES AVEC UN SEUL CHAR ( PAR EX t=oui)
//tester export oui=non oui=oui oui= oui=maybe
//		 export oui=non oui=yes

t_envlist *built_in_export(t_envlist *envlist, char **line)
{
	char		**variables;
	char		*tempo;
	char		**doubletempo;
	char		*quoteline;
	int			i;
	int			j;

	i = 0;
	j = 0;
	//ATTENTION SI LA VARIABLE MODIFIEE EST SHLVL
	//MODIFIER EGALEMENT 	envlist->shlvl_line = ;
	while(line[i])
		i++;
	if (i == 1 && ft_strcmp(line[0], "export") == 0 )//ATTENTION FONCTIONNE MEME AVEC PLEINS DE ' ' APRES
		printlist(envlist, 1);
	else
	{
		i = 1; // A MODIFIER PLUS TARD 
		variables = line;//ft_split(line, ' ');
		//free(line);   // free necessaire? 

		/*remplace pas les valeurs deja existantes
		export tout seul ne fonctionne pas*/
		while (variables[i])
		{
			if (checkvariable(variables[i]) == 1)
			{
				printf("bash: export: `%s': not a valid identifier\n",
					variables[i]);
				g_status = 1;//changer le retour d'erreur? // fonctione avec _ ? et $truc 
			}
			else if (searchequal(variables[i]))
			{
				while (variables[i][j] && variables[i][j] != '=')
					j++;
				tempo = ft_substr(variables[i], 0, j);
			//	printf("\n\ntempo = %s\n\n", tempo);
				doubletempo = ft_split(tempo, ' '); //a virer
				envlist = unset_line(doubletempo, envlist, 0);
				free(tempo);
				freetab(doubletempo); //a faire attention/virer
				j = 0;
			//	printf("\n\nquoteline = %s\n", variables[i]);
				quoteline = addquote(variables[i]);
			//	printf("quoteline = %s\n\n", quoteline);
				tempo = ft_strjoin("declare -x ", quoteline);
				free(quoteline);
				envlist = ft_add_env(envlist, tempo, 1);
				g_status = 0;
			}
			else
			{
				tempo = ft_strjoin("$", variables[i]);
				if (!(findline(envlist, tempo)))
				{
					if (tempo)
						free(tempo);
					tempo = ft_strjoin("declare -x ", variables[i]);
					envlist = ft_add_env(envlist, tempo, 1);
					g_status = 0;
				}
				else
					if (tempo)
						free(tempo);
			}
			i++;
		}
		//freetab(variables);
	}
	return (envlist);
}


// Minishell$> export " test"=oui
// bash: export: `"': not a valid identifier
// bash: export: `test"=oui': not a valid identifier

char	*addquote(char *line)
{
	char	*result;
	char	*tempo;
	char	*newline;
	int		equal;

	equal = 0;
	while (line[equal] && line[equal] != '=')
		equal++;
	tempo = ft_strndup(line, equal + 1);
	result = ft_strjoin(tempo, "\"");
	free(tempo);
	tempo = result;
//	printf("\n\nline = %s\n\n", line);
	newline = cutline(line);
//	printf("\n\nnewline = %s\n\n", newline);
	if (newline == NULL)
		result = ft_strjoin(tempo, "\0");
	else
	{
		result = ft_strjoin(tempo, newline);
		free(newline);
	}
	free(tempo);
	tempo = result;
	result = ft_strjoin(tempo, "\"" );
	free(tempo);
	return (result);
}
