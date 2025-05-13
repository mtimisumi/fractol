/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:05:23 by mmisumi           #+#    #+#             */
/*   Updated: 2024/11/11 14:23:07 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	lijst;
	int		cnt;

	cnt = 0;
	if (format == NULL)
		return (-1);
	va_start(lijst, format);
	while (*format)
	{
		if (*format == '%')
		{
			det_type(*(format + 1), &lijst, &cnt);
			format += 2;
		}
		else
		{
			write(1, format, 1);
			format++;
			cnt++;
		}
	}
	return (cnt);
}
