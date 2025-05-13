/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:27:55 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/23 16:28:07 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*q;
	char	*s;

	if (dest == 0 && src == 0)
		return (NULL);
	q = (char *) dest;
	s = (char *) src;
	while (n > 0)
	{
		if (dest > src)
		{
			q[n - 1] = s[n - 1];
			n--;
		}
		else
		{
			*q = *s;
			q++;
			s++;
			n--;
		}
	}
	return (dest);
}
