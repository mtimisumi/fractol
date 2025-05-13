/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:06:24 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/23 16:16:05 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*q;
	char	*s;

	if (dest == 0 && src == 0)
		return (NULL);
	q = (char *) dest;
	s = (char *) src;
	while (n > 0)
	{
		*q = *s;
		q++;
		s++;
		n--;
	}
	return (dest);
}
