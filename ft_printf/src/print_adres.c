/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_adres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:07:23 by mmisumi           #+#    #+#             */
/*   Updated: 2024/11/11 14:23:53 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

void	print_adres(void *lijst, int *cnt)
{
	uintptr_t	adres;

	if (!lijst)
	{
		write (1, "(nil)", 5);
		*cnt += 5;
		return ;
	}
	adres = (uintptr_t)lijst;
	write(1, "0x", 2);
	*cnt += 2;
	low_hexa(adres, cnt);
}
