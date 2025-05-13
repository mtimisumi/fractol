/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:14:10 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/13 14:52:38 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIDTH 2000 
#define	HEIGHT 1500
#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define MAGENTA 0x00FF00FF

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}			t_data;

typedef struct	s_cmplx
{
	float	zreal;
	float	zi;
	float	creal;
	float	ci;
}				t_cmplx;

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	t_data	data;
}			t_fractol;

typedef struct s_renderpix
{
	int		width;
	int		height;
	float	x_min;
	float	x_max;
	float	y_max;
	float	y_min;
}				t_renderpix;

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

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*point;

	point = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)point = color;
}

// __uint8_t	pixel_color(__uint8_t red, __uint8_t green, __uint8_t blue, __uint8_t alpha)
// {
// 	return (red << 24 || green << 16 || blue << 8 | alpha);
// }

__uint8_t	pixel_color(__uint8_t red, __uint8_t green, __uint8_t blue, __uint8_t alpha)
{
	return (alpha << 24 || red << 16 || green << 8 || blue );
}

void	render_pixel(int x, int y, t_cmplx *cmplx)
{
	t_renderpix	pix;
	float		aspect_ratio;
	float		new_x;
	float		new_y;

	pix.width = WIDTH;
	pix.height = HEIGHT;
	pix.x_min = -2.5;
	pix.x_max = 1.5;
	pix.y_max = 2;
	pix.y_min = -2;
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	new_x = ((float)x / WIDTH) * (pix.x_max - pix.x_min) + pix.x_min;
	new_y = ((float)y / HEIGHT) * (pix.y_max - pix.y_min) + pix.y_min;
	if (aspect_ratio > 1)
		new_x *= aspect_ratio;
	if (aspect_ratio < 1)
		new_y /= aspect_ratio;
	cmplx->creal = new_x;
	cmplx->ci = new_y;
}

int	calc_point(t_cmplx *cmplx)
{
	float	tmp_real;
	float	sum;
	int		i;

	tmp_real = 0;
	sum = 0;
	i = 0;
	cmplx->zreal = 0;
	cmplx->zi = 0;
	while (i < 200)
	{
		tmp_real = (cmplx->zreal * cmplx->zreal) - (cmplx->zi * cmplx->zi);
		cmplx->zi = (2 * cmplx->zreal * cmplx->zi);
		cmplx->zreal = tmp_real;

		cmplx->zreal += cmplx->creal;
		cmplx->zi += cmplx->ci;

		if ((cmplx->zreal * cmplx->zreal + cmplx->zi * cmplx->zi) > 4.0)
			return (i);
		i++;
	}
	return (i);
}

void	mandelbrot(t_fractol *fractol)
{
	t_cmplx	cmplx;
	int			x;
	int			y;
	int			color;

	x = 0;
	y = 0;
	color = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			render_pixel(x, y, &cmplx);
			color = calc_point(&cmplx);
			if (color >= 20 && color < 40)
				put_pixel(&fractol->data, x, y, RED);
			else if (color >= 40 && color < 70)
				put_pixel(&fractol->data, x, y, BLUE);
			else if (color >= 70 && color < 100)
				put_pixel(&fractol->data, x, y, GREEN);
			else if (color >= 100 && color < 200)
				put_pixel(&fractol->data, x, y, YELLOW);
			else if (color == 200)
				put_pixel(&fractol->data, x, y, MAGENTA);
			else
				put_pixel(&fractol->data, x, y, BLACK);
			x++;
		}
		y++;
		x = 0;
	}
}

int	keyhooks(int keysym, t_fractol *fractol)
{
	if (keysym == 65307)
		free_exit(fractol);
	return (0);
}

void	fractol()
{
	t_fractol	fractol;

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
	// mandelbrot(&fractol);
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.data.img, 0, 0);
	mlx_key_hook(fractol.win, keyhooks, &fractol);
	mlx_loop(fractol.mlx);
	free_exit(&fractol);
}

int	main(void)
{
	fractol();
	return (0);
}