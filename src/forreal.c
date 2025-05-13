/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forreal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:14:19 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/13 16:14:44 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIDTH 1000 
#define	HEIGHT 1000
#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define MAGENTA 0x00FF00FF

typedef struct s_data
{
	void	*img;
	char	*addr;
	//bits per pixel
	int		bpp;
	int		len;
	int		endian;
}			t_data;

typedef struct s_complex
{
	float	real;
	float	i;
}			t_complex;


typedef struct	s_fractol
{
	void		*mlx;
	void		*win;
	t_data		data;
}				t_fractol;

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
	//mlx destroy functions should be called (when something fails) in main function
	//mlx_destroy_window, mlx_destroy_display, mlx_destroy_image
	
	if (fractol->data.img)
		mlx_destroy_image(fractol->mlx, fractol->data.img);
	// if (fractol->data)
		// free(fractol->data);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	// if (fractol)
	// 	free(fractol);
	exit (1);
}
//returns float numbers resized to fit into mandelbrot so i can use for calculations
//aspect ratio means is defined as the ratio of the width of the screen to its height
// float	render_pixel(int xy, float new_min, float new_max, float old_max)
// {
// 	float	new_xy;
// 	float	new_pos;
// 	float	aspect_ratio;

// 	aspect_ratio = (float)WIDTH / (float)HEIGHT;
// 	new_xy = ((float)xy / old_max);
// 	new_pos = (new_xy * (new_max - new_min));
// 	return (new_pos + new_min);
// }

void	render_pixel(int x, int y, t_complex *z, t_complex *c)
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
	c->real = new_x;
	c->i = new_y;
}

//mandelbrot: z = z^2 + c (z starting at 0,0)
//first iteration will be c (x, yi)
//(x + yi)^2 = real(x^2 + y^2) + imaginary(2xyi)
//z = x^2 - y^2 + a + 2xiyb
//a: c's x-axis, b: c's y-axis
bool	calc_point(t_complex *z, t_complex *c)
{
	float	tmp_real;
	float	sum;
	int		i;

	tmp_real = 0;
	sum = 0;
	i = 0;

	z->real = 0;
	z->i = 0;
	while(i < 200)
	{
		//z^2
		tmp_real = (z->real * z->real) - (z->i * z->i);
		z->i = (2 * z->real * z->i);
		z->real = tmp_real;

		//z^2 + c
		z->real += c->real;
		z->i += c->i;

		if ((z->real *z->real + z->i * z->i) > 4.0)
			return (false);
		i++;
	}
	return (true);
}

//255 is full color
unsigned int	pixel_color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
	return (red << 24 || green << 16 | blue << 8 | alpha);
}

void	put_pixel(t_fractol *fractol, int x, int y, int color)
{
	char	*point;

	point = fractol->data.addr + (y * fractol->data.len + x * (fractol->data.bpp / 8));
	*(unsigned int*)point = color;
}

void	mandelbrot(t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
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
			render_pixel(x, y, &z, &c);
			if (calc_point(&z, &c) == false)
			{
				// color = pixel_color(0, 0, 0, 255);
				put_pixel(fractol, x, y, BLACK);
			}
			else
			{
				// color = pixel_color(255, 0, 0, 255);
				put_pixel(fractol, x, y, RED);
			}
			x++;
		}
		y++;
		x = 0;
	}
}

int	keyhooks(int keysym, t_fractol *fractol)
{
	if (keysym == 65307)
	{
		free_exit(fractol);
	}
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
	// put_pixel(&fractol, 4, 6, RED);
	mandelbrot(&fractol);
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
