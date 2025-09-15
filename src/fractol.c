/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:05:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/15 16:00:22 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calc_fractol(t_cmplx *cmplx, float iters)
{
	float	temp_real;
	int		i;

	temp_real = 0;
	i = 0;
	while (i < iters)
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

void	mandelbrot(t_fract *fract)
{
	t_cmplx		cmplx;
	int			x;
	int			y;
	int			color_index;
	uint32_t	palette[MAX_COLORS];

	x = 0;
	y = 0;
	color_index = 0;
	init_palette(palette);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			render_pixel(x, y, &cmplx, &fract->pix);
			cmplx.zreal = 0;
			cmplx.zi = 0;
			color_index = (calc_fractol(&cmplx, fract->pix.iters) * (MAX_COLORS - 1) / ITERS);
			put_pixel(&fract->data, x, y, palette[color_index]);
			x++;
		}
		y++;
		x = 0;
	}
}

void	julia(t_fract *fract)
{
	t_cmplx		cmplx;
	int			x;
	int			y;
	int			color_index;
	uint32_t	palette[MAX_COLORS];

	x = 0;
	y = 0;
	color_index = 0;
	init_palette(palette);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			render_pixel(x, y, &cmplx, &fract->pix);
			cmplx.creal = fract->julia_real;
			cmplx.ci = fract->julia_i;
			color_index = (calc_fractol(&cmplx, fract->pix.iters) * (MAX_COLORS - 1) / ITERS);
			put_pixel(&fract->data, x, y, palette[color_index]);
			x++;
		}
		y++;
		x = 0;
	}
}

void	create_fractol(t_fract *fract)
{
	init_pix(&fract->pix);
	fract->mlx = mlx_init();
	if (!fract->mlx)
		free_exit(fract);
	fract->win = mlx_new_window(fract->mlx, WIDTH, HEIGHT, "fractol");
	if (!fract->win)
		free_exit(fract);
	fract->data.img = mlx_new_image(fract->mlx, WIDTH, HEIGHT);
	if (!fract->data.img)
		free_exit(fract);
	fract->data.addr = mlx_get_data_addr(fract->data.img,
			&fract->data.bpp, &fract->data.len, &fract->data.endian);
	if (!fract->data.addr)
		free_exit(fract);
	if (fract->fractol == MANDELBROT)
		mandelbrot(fract);
	else
		julia(fract);
	mlx_put_image_to_window(fract->mlx, fract->win, fract->data.img, 0, 0);
	mlx_hook(fract->win, 17, 0, close_window, fract);
	mlx_hook(fract->win, 4, 4, mouse, fract);
	mlx_key_hook(fract->win, keyhooks, fract);
	mlx_loop(fract->mlx);
	free_exit(fract);
}
