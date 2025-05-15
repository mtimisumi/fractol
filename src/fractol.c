/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:05:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/15 15:27:08 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calc_fractol(t_cmplx *cmplx)
{
	float	temp_real;
	int		i;

	temp_real = 0;
	i = 0;
	while (i < ITERS)
	{
		temp_real = (cmplx->zreal * cmplx->zreal) - (cmplx->zi * cmplx->zi);
		cmplx->zi = (2 * cmplx->zreal * cmplx->zi);
		cmplx->zreal = temp_real;

		cmplx->zreal += cmplx->creal;
		cmplx->zi += cmplx->ci;

		if ((cmplx->zreal * cmplx->zreal + cmplx->zi * cmplx->zi) > 4.0)
			return (i);
		i++;
	}
	return (i);
}

// void	calc_julia(t_cmplx *cmplx)
// {
// 	float	temp_real;
// 	int		i;

// 	temp_real = 0;
// 	i = 0;
// 	while (i < ITERS)
// 	{
// 		temp_real = (cmplx->zreal * cmplx->zreal) - (cmplx->zi * cmplx->zi);
// 		cmplx->zi = (2 * cmplx->zreal * cmplx->zi);
// 		cmplx->zreal = temp_real;

// 		cmplx->zreal += cmplx->creal;
// 		cmplx->zi += cmplx->ci;

// 		if ((cmplx->zreal * cmplx->zreal + cmplx->zi * cmplx->zi) > 4.0)
// 			return (i);
// 		i++;
// 	}
// 	return (i);
// }

void	mandelbrot(t_fractol *fractol)
{
	t_cmplx	cmplx;
	int			x;
	int			y;
	int			color;
	int			index;

	x = 0;
	y = 0;
	color = 0;
	index = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			render_pixel(x, y, &cmplx, &fractol->pix);
			cmplx.zreal = 0;
			cmplx.zi = 0;
			color = calc_fractol(&cmplx);
			index = (color * (MAX_COLORS - 1) / ITERS);
			put_pixel(&fractol->data, x, y, fractol->palette[index]);
			// if (color >= (WIDTH / 50 / 2) && color < (WIDTH / 25 / 2))
			// 	put_pixel(&fractol->data, x, y, pixel_color(255, 0, 0, 255));
			// else if (color >= (WIDTH / 25 / 2) && color < (WIDTH / 14 / 2))
			// 	put_pixel(&fractol->data, x, y, pixel_color(0, 0, 255, 255));
			// else if (color >= (WIDTH / 14 / 2) && color < (WIDTH / 10 / 2))
			// 	put_pixel(&fractol->data, x, y, pixel_color(0, 255, 255, 255));
			// else if (color >= (WIDTH / 10 / 2) && color < (WIDTH / 5 / 2))
			// 	put_pixel(&fractol->data, x, y, pixel_color(255, 255, 0, 255));
			// else if (color == (WIDTH / 5 / 2))
			// 	put_pixel(&fractol->data, x, y, pixel_color(0, 0, 255, 255));
			// else
			// 	put_pixel(&fractol->data, x, y, pixel_color(0, 0, 0, 255));
			x++;
		}
		y++;
		x = 0;
	}
}

void	julia(t_fractol *fractol)
{
	t_cmplx	cmplx;
	int		x;
	int		y;
	int		color;

	x = 0;
	y = 0;
	color = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			render_pixel(x, y, &cmplx, &fractol->pix);
			cmplx.creal = fractol->julia_real;
			cmplx.ci = fractol->julia_i;
			color = calc_fractol(&cmplx);
			if (color >= (WIDTH / 50 / 2) && color < (WIDTH / 25 / 2))
				put_pixel(&fractol->data, x, y, pixel_color(255, 0, 0, 255));
			else if (color >= (WIDTH / 25 / 2) && color < (WIDTH / 14 / 2))
				put_pixel(&fractol->data, x, y, pixel_color(0, 0, 255, 255));
			else if (color >= (WIDTH / 14 / 2) && color < (WIDTH / 10 / 2))
				put_pixel(&fractol->data, x, y, pixel_color(0, 255, 255, 255));
			else if (color >= (WIDTH / 10 / 2) && color < (WIDTH / 5 / 2))
				put_pixel(&fractol->data, x, y, pixel_color(255, 255, 0, 255));
			else if (color == (WIDTH / 5 / 2))
				put_pixel(&fractol->data, x, y, pixel_color(0, 0, 255, 255));
			else
				put_pixel(&fractol->data, x, y, pixel_color(0, 0, 0, 255));
			x++;
			
		}
		y++;
		x = 0;
	}
}

void	fractol(int argc, char **argv)
{
	t_fractol	fractol;
	init_palette(fractol.palette);
	init_pix(&fractol.pix);
	fractol.mlx = mlx_init();
	if (!fractol.mlx)
		free_exit(&fractol);
	fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, "mandelbrot");
	if (!fractol.win)
		free_exit(&fractol);
	fractol.data.img = mlx_new_image(fractol.mlx, WIDTH, HEIGHT);
	if (!fractol.data.img)
		free_exit(&fractol);
	fractol.data.addr = mlx_get_data_addr(fractol.data.img, &fractol.data.bpp, &fractol.data.len, &fractol.data.endian);
	if (!fractol.data.addr)
		free_exit(&fractol);
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
	{
		fractol.fractol = MANDELBROT;
		mandelbrot(&fractol);
	}
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
	{
		fractol.fractol = JULIA;
		fractol.julia_real = to_float(argv[2]);
		fractol.julia_i = to_float(argv[3]);
		julia(&fractol);
	}
	else
	{
		fractol.fractol = JULIA;
		fractol.julia_real = to_float(argv[1]);
		fractol.julia_i = to_float(argv[2]);
		julia(&fractol);
	}
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.data.img, 0, 0);
	mlx_hook(fractol.win, 17, 0, close_window, &fractol);
	mlx_hook(fractol.win, 4, 4, click, &fractol);
	mlx_key_hook(fractol.win, keyhooks, &fractol);
	mlx_loop(fractol.mlx);
	free_exit(&fractol);
}
