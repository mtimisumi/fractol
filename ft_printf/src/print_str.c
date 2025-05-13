/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:03:07 by mmisumi           #+#    #+#             */
/*   Updated: 2024/11/09 15:44:24 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_str(char *str, int *cnt)
{
	if (str == NULL)
	{
		*cnt += write(1, "(null)", 6);
		return ;
	}
	while (*str)
	{
		write(1, str, 1);
		str++;
		*cnt += 1;
	}
}
