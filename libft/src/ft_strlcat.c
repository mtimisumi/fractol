/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:43:31 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/21 18:00:57 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d;
	size_t	s;

	d = 0;
	s = 0;
	while (dst[d] != '\0' && size > d)
		d++;
	while (src[s] != '\0')
		s++;
	if (d >= size)
		return (size + s);
	i = d;
	while (size > i + 1 && *src)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	if (size > i)
		dst[i] = '\0';
	return (d + s);
}
