/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:57:15 by dabey             #+#    #+#             */
/*   Updated: 2023/01/20 22:04:32 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list_token(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->token);
		free(tmp);
		// tmp = token;
	}
}

void	printlist_token(t_token *token)
{
	t_token	*tempo;

	if (!token)
		return ;
	tempo = token;
	while (tempo)
	{
		printf("*****token*****\n");
		printf("%s\n", tempo->token);
		printf("%d\n", tempo->type);
		printf("\n");
		tempo = tempo->next;
	}
}

t_token	*ft_new_token(char *str, enum_type type)
{
	t_token	*new;

	if (str == NULL)
		return (NULL);
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_add_token(t_token **token, char *str, enum_type type)
{
	t_token	*head;
	t_token	*new;

	head = NULL;
	new = ft_new_token(str, type);
	if (!(*token))
		*token = new;
	else
	{
		head = *token;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
}
