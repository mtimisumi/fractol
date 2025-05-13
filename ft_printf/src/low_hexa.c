/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_hexa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:06:01 by mmisumi           #+#    #+#             */
/*   Updated: 2024/11/09 15:43:44 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	low_hexa(unsigned long number, int *cnt)
{
	unsigned int	c;
	const char		str[] = "0123456789abcdef";

	if (number >= 16)
	{
		low_hexa(number / 16, cnt);
	}
	c = (number % 16);
	write (1, &str[c], 1);
	*cnt += 1;
}
