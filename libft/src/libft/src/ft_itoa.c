/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:45:43 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/23 15:40:48 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*makingthestring(int n, int len, int neg)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (neg == -1)
	{
		str[0] = '-';
	}
	len--;
	while (len >= 0)
	{
		if (len == 0 && neg == -1)
			break ;
		str[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (str);
}

static char	*int_min(void)
{
	const char		min_int[] = "-2147483648";
	const size_t	len = sizeof(char) * (11 + 1);
	char			*str;
	size_t			i;

	i = 0;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = min_int[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	int		temp;

	if (n == -2147483648)
		return (int_min());
	temp = n;
	len = 0;
	if (n == 0)
		len++;
	neg = 1;
	while (temp != 0)
	{
		len++;
		temp /= 10;
	}
	if (n < 0)
	{
		neg = -1;
		n = -n;
		len++;
	}
	return (makingthestring(n, len, neg));
}
