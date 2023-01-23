#include "../includes/minishell.h"

int built_in_exit(t_list *list)
{
    int i;

    i = 0;
    if(list->cmd[1])
    {
        while (list->cmd[1][i] >= 48 && list->cmd[1][i] <= 57)
            i++;
        if (i != ft_strlen(list->cmd[1]))
        {
            write(2, "bash: exit: ", 12);
            write(2, list->cmd[1], ft_strlen(list->cmd[1]));
            write(2, ": numeric argument required\n", 28);
            g_status = 1;
        }
        else if(list->cmd[2])
        {
            write(2, "bash: exit: too many arguments\n", 31);
            g_status = 1;
        }
        else
		    g_status = ft_atoi(list->cmd[1]);;//adapter si au dessus de 256 ou negatif -> cas particulier
    }
    else
        g_status = 0;
    list->exit = 1;
    return (1);
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
	while(line[i] && lineisn(line[i]) == 1)
		i++;
	return (i - 1);
}

int built_in_echo(char **line)
{
    int  i;
	int		check;
    int  linelength;

    i = 0;
    check = 0;
    linelength = 0;
	while(line[linelength])
        linelength++;
    if (line[1])
        check = checkn(line);
    if (check > 0)
        i += check;
    while (i < linelength - 1)
    {
        if (i == linelength - 2)
            printf("%s", line[i + 1]);
        else
            printf("%s ", line[i + 1]);
        i++;
    }
    if (check == 0)
        printf("\n");
    return (1);
}
