/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:04:16 by mmisumi           #+#    #+#             */
/*   Updated: 2024/11/11 14:23:24 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	det_type(const char spess, va_list *lijst_ptr, int *cnt)
{
	if (spess == 'c')
		print_char((char)va_arg(*lijst_ptr, int), cnt);
	else if (spess == 's')
		print_str(va_arg(*lijst_ptr, char *), cnt);
	else if (spess == 'p')
		print_adres(va_arg(*lijst_ptr, void *), cnt);
	else if (spess == 'd' || spess == 'i')
		print_nbr(va_arg(*lijst_ptr, int), cnt);
	else if (spess == 'u')
		put_u(va_arg(*lijst_ptr, unsigned int), cnt);
	else if (spess == 'x')
		low_hexa(va_arg(*lijst_ptr, unsigned int), cnt);
	else if (spess == 'X')
		upp_hexa(va_arg(*lijst_ptr, unsigned int), cnt);
	else if (spess == '%')
	{
		write(1, "%%", 1);
		*cnt += 1;
	}
}
