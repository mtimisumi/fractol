/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:51:17 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/12 15:29:53 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_free()
{
	exit(1);
}

void	julia(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_printf("julia\n");
	// if (argc == 2)
	exit_free();
}

void	mandelbrot(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_printf("mandelbrot\n");
	exit_free();
}

//still to do
bool	is_valid(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if ((str[i] == '+' || str[i] == '-') && ft_strlen(str) > 1)
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
	}
	return (0);
}

void	available_params()
{
	ft_printf("Invalid parameters,\n");
	ft_printf("Some available parameters:\n\n");
	ft_printf("mandelbrot\njulia\njulia -1,12 1,453\n");
	exit(2);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 || argc == 4)
	{
		if ((argc == 2) && ft_strncmp(argv[1], "mandelbrot", 11) == 0)
			mandelbrot(argc, argv);
		else if ((argc == 2) && ft_strncmp(argv[1], "julia", 6) == 0)
			julia(argc, argv);
		else if ((argc == 4) && ft_strncmp(argv[1], "julia", 6) == 0)
		{
			if (is_valid(argv[3]) && is_valid(argv[4]))
				julia(argc, argv);
		}
	}
	available_params();
	return (0);
}
