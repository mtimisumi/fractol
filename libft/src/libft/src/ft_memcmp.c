/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:53:10 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/23 16:35:57 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*q1;
	const unsigned char	*q2;

	q1 = (const unsigned char *)s1;
	q2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 1)
	{
		if (*q1 != *q2)
			return (*q1 - *q2);
		n--;
		q1++;
		q2++;
	}
	if (n == 0)
		return (0);
	return (*q1 - *q2);
}
