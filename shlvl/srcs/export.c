#include "../includes/minishell.h"

int	searchequal(char *line)
{
	int	i;

    i = 1;
	while (line[i])
	{
		if (line[i] == '=')
			return (i - 1);
		i++;
	}
	return (0);
}

int	checkvariable(char *line) //gerer les $?
{
	int	i;

	i = 0;
	if (line[i] == '=')
		return (1);
	while (line[i] && line[i] != '=')
	{
		if (line[i] != '_' && (line[i] < 65 || line[i] > 90)
			&& (line[i] < 97 || line[i] > 122))
			return (1);
		i++;
	}
	return (0);
}

t_envlist *built_in_export(t_envlist *envlist, char *line)
{
	char		**variables;
	char		*tempo;
	char		*quoteline;
	int			i;
	int			j;

	i = 0;
	j = 0;

	if (ft_strrchr(line, ' ') == 0)//ATTENTION FONCTIONNE MEME AVEC PLEINS DE ' ' APRES
		printlist(envlist, 1);
	else
	{
		i = 1; // A MODIFIER PLUS TARD 
		variables = ft_split(line, ' ');
		//free(line);   // free necessaire? 
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
				envlist = unset_line(tempo, envlist);
				j = 0;
				quoteline = addquote(variables[i]);
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
		freetab(variables);
	}
	return (envlist);
}

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
	newline = cutline(line);
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
