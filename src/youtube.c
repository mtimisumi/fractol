/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   youtube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:10:52 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/07 16:10:54 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MALLOC_ERROR 1
#define MLX_ERROR 1
#define WIDTH 400
#define HEIGHT 400

int	main(void)
{
	t_complex	z;
	t_complex	c;
	double		temp_real;

	z.real = 0;
	z.i = 0;
	c.real = 5;
	c.i = 2;

	int	i = 0;
	while (i < 42)
	{
		//General formula
		//z = z^2 + c;
		temp_real = (z.real * z.real) - (z.i * z.i);
		z.i = 2 * z.real * z.i;
		z.real = temp_real;

		//Adding the c value
		z.real += c.real;
		z.i += c.i;

		printf("interation n -> %d, \t real %f, \t imaginary %f\n", i, z.real, z.i);
		i++;
	}
	return (0);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	return (0);
}

int	main(void)
{
	t_mlx_data	data;

	data.mlx_ptr = mlx_init();

	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}
	mlx_key_hook(data.win_ptr, handle_input(), &data);
	mlx_loop(data.mlx_ptr);
return (0);
}

int	main(void)
{
	void	*mlx_connection;
	void	*window1;
	void	*window2;

	mlx_connection = mlx_init();
	if (mlx_connection == NULL)
		return (MALLOC_ERROR);
	window1 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "window 1");
	if (window1 == NULL)
	{
		mlx_destroy_display(mlx_connection);
		free(mlx_connection);
		return (MALLOC_ERROR);
	}
	window2 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "window 2");
	if (window2 == NULL)
	{
		mlx_destroy_display(mlx_connection);
		free(mlx_connection);
		return (MALLOC_ERROR);
	}
	mlx_loop(mlx_connection);
	return (0);
}
