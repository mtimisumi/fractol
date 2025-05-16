/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:14:10 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/16 13:35:03 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	available_params(void)
{
	ft_printf("Invalid parameters,\n");
	ft_printf("Some available parameters:\n\n");
	ft_printf(" mandelbrot\n julia\n julia -1,12 1,453\n");
	exit(2);
}

void	free_exit(t_fract *fract)
{
	if (fract->data.img)
		mlx_destroy_image(fract->mlx, fract->data.img);
	if (fract->win)
		mlx_destroy_window(fract->mlx, fract->win);
	if (fract->mlx)
	{
		mlx_destroy_display(fract->mlx);
		free(fract->mlx);
	}
	exit (1);
}

void	init_julia(int argc, char **argv, t_fract *fract)
{
	fract->fractol = JULIA;
	if (argc == 4)
	{
		fract->julia_real = to_float(argv[2]);
		fract->julia_i = to_float(argv[3]);
	}
	else if (argc == 3)
	{
		fract->julia_real = to_float(argv[1]);
		fract->julia_i = to_float(argv[2]);
	}
	else
	{
		fract->julia_real = -0.00932;
		fract->julia_i = 0.7432;
	}
}

int	main(int argc, char *argv[])
{
	t_fract	fract;

	if ((argc == 2) && ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fract.fractol = MANDELBROT;
	else if ((argc == 2) && ft_strncmp(argv[1], "julia", 6) == 0)
		init_julia(argc, argv, &fract);
	else if (argc == 4 && ft_strncmp(argv[1], "julia", 6) == 0
		&& is_julia_coordinate(argv[2]) && is_julia_coordinate(argv[3]))
		init_julia(argc, argv, &fract);
	else if (argc == 3 && is_julia_coordinate(argv[1])
		&& is_julia_coordinate(argv[2]))
		init_julia(argc, argv, &fract);
	else
		available_params();
	if (fract.fractol == MANDELBROT || fract.fractol == JULIA)
		create_fractol(&fract);
	return (0);
}
