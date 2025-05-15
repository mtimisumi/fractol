/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:08:18 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/15 13:49:08 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	keyhooks(int keysym, t_fractol *fractol)
{
	if (keysym == XK_Escape)
		free_exit(fractol);
	if (keysym == XK_w || keysym == XK_s)
		zoomin(keysym, fractol);
	return (0);
}

int	close_window(t_fractol *fractol)
{
	free_exit(fractol);
	exit (1);
	return (0);
}

void	zoomin(int keysym, t_fractol *fractol)
{
	float x;

	x = 1;
	if (keysym == XK_w)
		x = 0.90;
	if (keysym == XK_s)
		x = 1.10;
	fractol->pix.x_min *= x;
	fractol->pix.x_max *= x;
	fractol->pix.y_max *= x;
	fractol->pix.y_min *= x;
	if (fractol->fractol == MANDELBROT)
		mandelbrot(fractol);
	else
		julia(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->data.img, 0, 0);
}

//only problem is clock and zoomin dont work together.
int	click(int button, int px, int py, t_fractol *fractol)
{
	t_pix	*pix;
	float	xcenter;
	float	ycenter;
	float	add_half_x;
	float	add_half_y;

	pix = &fractol->pix;
	add_half_x = (pix->x_max - pix->x_min) / 2;
	add_half_y = (pix->y_max - pix->y_min) / 2;
	if (button == 1)
	{
		xcenter = ((float)px / WIDTH) * (pix->x_max - pix->x_min) + pix->x_min;
		ycenter = ((float)py / HEIGHT) * (pix->y_max - pix->y_min) + pix->y_min;
		pix->x_min = xcenter - add_half_x;
		pix->x_max = xcenter + add_half_x;
		pix->y_max = ycenter + add_half_y;
		pix->y_min = ycenter - add_half_y;
	}
	if (fractol->fractol == MANDELBROT)
		mandelbrot(fractol);
	else
		julia(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->data.img, 0, 0);
	return (0);
}
