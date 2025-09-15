/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:08:18 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/15 16:01:37 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	keyhooks(int keysym, t_fract *fract)
{
	if (keysym == XK_Escape)
		free_exit(fract);
	if (keysym == XK_w || keysym == XK_s
		|| keysym == XK_a || keysym == XK_d)
		move(keysym, fract);
	if (keysym == XK_Up || keysym == XK_Down)
		zoom(keysym, fract);
	if (keysym == XK_Left || keysym == XK_Right)
		change_iters(keysym, fract);
	put_image(fract);
	return (0);
}

void	put_image(t_fract *fract)
{
	if (fract->fractol == MANDELBROT)
		mandelbrot(fract);
	else
		julia(fract);
	mlx_put_image_to_window(fract->mlx, fract->win, fract->data.img, 0, 0);
}

int	close_window(t_fract *fract)
{
	free_exit(fract);
	exit (1);
	return (0);
}

int	mouse(int button, int x, int y, t_fract *fract)
{
	if (button == 1)
		click(button, x, y, fract);
	if (button == 4 || button == 5)
		scroll(button, fract);
	put_image(fract);
	return (0);
}
