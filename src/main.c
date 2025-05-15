/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:14:10 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/15 15:01:18 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	available_params()
{
	ft_printf("Invalid parameters,\n");
	ft_printf("Some available parameters:\n\n");
	ft_printf(" mandelbrot\n julia\n julia -1,12 1,453\n");
	exit(2);
}

void	free_exit(t_fractol *fractol)
{	
	if (fractol->data.img)
		mlx_destroy_image(fractol->mlx, fractol->data.img);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	exit (1);
}

int	main(int argc, char *argv[])
{
	if ((argc == 2) && ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol(argc, argv);
	else if ((argc == 2) && ft_strncmp(argv[1], "julia", 6) == 0)
		fractol(argc, argv);
	else if ((argc == 4) && (ft_strncmp(argv[1], "julia", 6) == 0) &&
		is_julia_coordinate(argv[2]) && is_julia_coordinate(argv[3]))
			fractol(argc, argv);
	else if (argc == 3 && is_julia_coordinate(argv[1]) && is_julia_coordinate(argv[2]))
		fractol(argc, argv);
	else
		available_params();
	return (0);
	}
