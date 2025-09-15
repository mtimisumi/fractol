/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:12:09 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/15 15:58:37 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	pixel_color(int alpha, int red, int green, int blue)
{
	return (alpha << 24 | red << 16 | green << 16 | blue);
}

void	init_palette(uint32_t *palette)
{
	if (!palette)
		return ;
	palette[0] = pixel_color(255, 0, 0, 0);
	palette[1] = pixel_color(255, 0, 0, 255);
	palette[2] = pixel_color(255, 255, 0, 255);
	palette[3] = pixel_color(255, 255, 0, 0);
	palette[4] = pixel_color(255, 0, 0, 0);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*point;

	point = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)point = color;
}

void	init_pix(t_pix *pix)
{
	float	aspect_ratio;

	pix->width = WIDTH;
	pix->height = HEIGHT;
	pix->x_min = -2.0;
	pix->x_max = 2.0;
	pix->y_max = 2.0;
	pix->y_min = -2.0;
	pix->iters = ITERS;
	aspect_ratio = pix->width / pix->height;
	if (aspect_ratio > 1)
	{
		pix->y_min /= aspect_ratio;
		pix->y_max /= aspect_ratio;
	}
	if (aspect_ratio < 1)
	{
		pix->x_min /= aspect_ratio;
		pix->x_max /= aspect_ratio;
	}
}

void	render_pixel(int x, int y, t_cmplx *cmplx, t_pix *pix)
{
	float		new_x;
	float		new_y;

	new_x = ((float)x / WIDTH) * (pix->x_max - pix->x_min) + pix->x_min;
	new_y = ((float)y / HEIGHT) * (pix->y_max - pix->y_min) + pix->y_min;
	cmplx->creal = new_x;
	cmplx->ci = new_y;
	cmplx->zreal = new_x;
	cmplx->zi = new_y;
}
