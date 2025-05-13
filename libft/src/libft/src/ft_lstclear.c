/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:41:36 by mmisumi           #+#    #+#             */
/*   Updated: 2024/10/29 16:03:34 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tptr;

	while (*lst)
	{
		tptr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tptr;
	}
	*lst = NULL;
}
