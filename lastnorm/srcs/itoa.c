/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:48:49 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/01/26 15:48:55 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long	ft_atoi(const char *str)
{
	long long	signe;
	long long	i;
	long long	num;

	i = 0;
	signe = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * signe);
}

int	itoanega(long long *n, long long *negative)
{
	if (*n < 0)
	{
		*n *= -1;
		*negative = 1;
		return (1);
	}
	return (0);
}

void	itoalen(long long *tmpn, long long *len)
{
	while (*tmpn > 9)
	{
		(*len)++;
		*tmpn /= 10;
	}
}

char	*ft_itoa(long long n)
{
	long long		tmpn;
	long long		len;
	char			*str;
	long long		negative;

	if (n == -2147483648)
		return ((char *)ft_strdup("2147483648"));
	negative = 0;
	tmpn = n;
	len = 2;
	itoalen(&tmpn, &len);
	len += itoanega(&n, &negative);
	str = malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}
