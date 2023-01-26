#include "../includes/minishell.h"
/*
void	is_redi(char *line, int *i, enum_type *redi_type)
{
	if (line[*i] == '>')
	{
		if (line[++*i] == '>')
			*redi_type = 5;
		else
			*redi_type = 3;
	}
	else if (line[*i] == '<')
	{
		if (line[++*i] == '<')
			*redi_type = 4;
		else
			*redi_type = 2;
	}
	if (*redi_type == 5 || *redi_type == 4)
		++*i;
}

char	*get_char_redi(enum_type redi_type)
{
	char *word;

	if (redi_type == 5 || redi_type == 4)
		word = malloc(sizeof(char) * 3);
	else
		word = malloc(sizeof(char) * 2);
	if (!word)
		return (NULL);
	if (redi_type == 4)
		word = "<<";
	else if (redi_type == 5)
		word = ">>";
	else if (redi_type == 2)
		word = "<";
	else
		word = ">";
	return (word);
}

char	*get_file_name(t_token **token, char *line, int *i)
{
	// int i;

	// i = 0;
	while (line[*i])
	{
		while (line[*i] == ' ')
			*i++;
		if (is_word(line[*i]) == 1)
			get_word(line, i);
	}
}

// void	get_rediout_file(t_token **token, char *line)
// {

// }

// void	get_append_file(t_token **token, char *line)
// {

// }

// void	get_herdoc_file(t_token **token, char *line)
// {

// }

void	get_redi_and_word(t_token **token, char *line, int *i, char c)
{
	char		*str;
	enum_type	type;

	while (line[*i])
	{
		if (ft_strcmp(line + *i, "<") == 1)
		{
			get_redin_file(&token, line, *i++);
		}
		// else if (ft_strcmp(line + *i, "<") == 1)
		// {
		// 	get_rediout_file(&token, line + *i + 2);
		// }
		// else if (ft_strcmp(line + *i, ">>") == 1)
		// {
		// 	get_append_file(&token, line + *i + 2);
		// }
		// else if (ft_strcmp(line + *i, "<<") == 1)
		// {
		// 	get_herdoc_file(&token, line + *i + 2);
		// }
	}
}

t_token	*ft_creat_token(t_token **token, char **cmd)
{
	int			i;
	int			j;
	char		*word;
	enum_type	redi_type;

	i = 0;
	word = NULL;

	redi_type = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			is_redi(cmd[i], &i, &redi_type);
			if (redi_type)
			{
				word = get_char_redi(redi_type);
				ft_add_token(&token, word, redi_type);
				word = get_file_name();
			}
	}
	return (token);
}

*/