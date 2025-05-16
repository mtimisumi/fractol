/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:30 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/16 13:31:26 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move(int keysym, t_fract *fract)
{
	float	x_range;
	float	y_range;

	x_range = fract->pix.x_max - fract->pix.x_min;
	y_range = fract->pix.y_max - fract->pix.y_min;
	if (keysym == XK_w)
	{
		fract->pix.y_max -= 0.10 * y_range;
		fract->pix.y_min -= 0.10 * y_range;
	}
	if (keysym == XK_s)
	{
		fract->pix.y_max += 0.10 * y_range;
		fract->pix.y_min += 0.10 * y_range;
	}
	if (keysym == XK_a)
	{
		fract->pix.x_max -= 0.10 * x_range;
		fract->pix.x_min -= 0.10 * x_range;
	}
	if (keysym == XK_d)
	{
		fract->pix.x_max += 0.10 * x_range;
		fract->pix.x_min += 0.10 * x_range;
	}
}

void	scroll(int button, t_fract *fract)
{
	float	x;
	float	x_range;
	float	y_range;

	x = 1;
	x_range = fract->pix.x_max - fract->pix.x_min;
	y_range = fract->pix.y_max - fract->pix.y_min;
	if (button == 4)
	{
		fract->pix.x_max -= (x_range * 0.10);
		fract->pix.x_min += (x_range * 0.10);
		fract->pix.y_max -= (y_range * 0.10);
		fract->pix.y_min += (y_range * 0.10);
	}
	if (button == 5)
	{
		fract->pix.x_max += (x_range * 0.10);
		fract->pix.x_min -= (x_range * 0.10);
		fract->pix.y_max += (y_range * 0.10);
		fract->pix.y_min -= (y_range * 0.10);
	}
}

void	click(int button, int px, int py, t_fract *fract)
{
	t_pix	*pix;
	float	xcenter;
	float	ycenter;
	float	add_half_x;
	float	add_half_y;

	pix = &fract->pix;
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
}
