/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:40:44 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/23 15:41:22 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reset(size_t *i, size_t *j, size_t *l)
{
	*i += 1;
	*l += *j - 1;
	*j = 0;
	return ;
}

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (lit[0] == '\0')
		return ((char *)big);
	while (big[i] && len > 0)
	{
		if (big[i] != lit[j])
		{
			i++;
			len--;
		}
		if (big[i] == lit[j])
		{
			while ((big[i + j] == lit[j]) && lit[j] != '\0' && len-- > 0)
				j++;
			if (lit[j] == '\0')
				return ((char *)&big[i]);
			reset(&i, &j, &len);
		}
	}
	return (NULL);
}
