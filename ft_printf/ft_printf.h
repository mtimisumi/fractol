/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:08:59 by mmisumi           #+#    #+#             */
/*   Updated: 2024/11/11 14:23:37 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

void	det_type(const char spess, va_list *lijst_ptr, int *cnt);
int		ft_printf(const char *format, ...);
void	low_hexa(unsigned long number, int *cnt);
void	print_adres(void *lijst, int *cnt);
void	print_char(char c, int *cnt);
void	print_nbr(int n, int *cnt);
void	print_str(char *str, int *cnt);
void	put_u(unsigned int n, int *cnt);
void	upp_hexa(unsigned long number, int *cnt);

#endif
