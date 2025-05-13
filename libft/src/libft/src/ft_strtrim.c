/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:37:31 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/22 19:43:41 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		beg;
	int		end;
	char	*trimstr;

	beg = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[beg]) != NULL)
		beg++;
	while (ft_strrchr(set, s1[end]) != NULL)
		end--;
	trimstr = ft_substr(s1, beg, end + 1 - beg);
	return (trimstr);
}
