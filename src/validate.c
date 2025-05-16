/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:11 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/15 19:33:05 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	decimals(char *str)
{
	int		i;
	float	nbr;
	int		divide;

	i = 0;
	nbr = 0;
	divide = 10;
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		nbr += str[i] - '0';
		if (str[i + 1] != '\0')
		{
			nbr *= 10;
			divide *= 10;
		}
		i++;
	}
	nbr /= divide;
	return (nbr);
}

float	to_float(char *str)
{
	int		i;
	int		sign;
	float	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] != '.')
	{
		nbr += (str[i] - '0');
		if (str[i + 1] != '\0' && str[i + 1] != '.')
			nbr *= 10;
		i++;
	}
	return ((nbr + decimals(str)) * sign);
}

bool	is_julia_coordinate(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i + 1] == '.' && ft_strlen(str) > 8)
		return (false);
	else if (str[i + 1] != '.' && ft_strlen(str) > 7)
		return (false);
	if (to_float(str) < -2.0 || to_float(str) > 2.0)
		return (false);
	return (true);
}
