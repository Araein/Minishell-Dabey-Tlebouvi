/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:24:42 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/28 22:53:12 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in_exit(t_list *list, int i)
{
	if (list->cmd[1])
	{
		if (list->cmd[1][i] == 45)
			i++;
		while (list->cmd[1][i] >= 48 && list->cmd[1][i] <= 57)
			i++;
		if (i != ft_strlen(list->cmd[1]))
		{
			write(2, "bash: exit: ", 12);
			write(2, list->cmd[1], ft_strlen(list->cmd[1]));
			write(2, ": numeric argument required\n", 28);
			g_status = 2;
		}
		else if (list->cmd[2])
		{
			write(2, "bash: exit: too many arguments\n", 31);
			g_status = 1;
		}
		else
			g_status = ft_atoi(list->cmd[1]);
	}
	else
		g_status = 0;
	return (1);
}

int	lineisn(char *line)
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

int	checkn(char **line)
{
	int	i;

	i = 1;
	while (line[i] && lineisn(line[i]) == 1)
		i++;
	return (i - 1);
}

int	built_in_echo(char **line, t_list *list)
{
	int	i;
	int	check;
	int	linelength;

	redirectthis(list);
	i = 0;
	check = 0;
	linelength = 0;
	while (line[linelength])
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

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*answer;
	int		i;

	i = 0;
	if (!s || len <= 0 || start >= (unsigned int)ft_strlen(s))
		return (NULL);
	answer = malloc(sizeof(char) * len + 1);
	if (answer == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		answer[i] = s[start];
		i++;
		start++;
	}
	answer[i] = '\0';
	return (answer);
}
