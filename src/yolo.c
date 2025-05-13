/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:14:10 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/13 18:12:52 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIDTH 1000
#define	HEIGHT 800
#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define MAGENTA 0x00FF00FF
#define INDIGO 0x004B0082

void	available_params()
{
	ft_printf("Invalid parameters,\n");
	ft_printf("Some available parameters:\n\n");
	ft_printf(" mandelbrot\n julia\n julia -1,12 1,453\n");
	exit(2);
}

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

__uint32_t	pixel_color(__uint32_t red, __uint32_t green, __uint32_t blue, __uint32_t alpha)
{
	return (alpha << 24 |red << 16 | green << 16 | blue);
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
	cmplx->zreal = new_x;
	cmplx->zi = new_y;
}

int	calc_mandelbrot(t_cmplx *cmplx)
{
	float	tmp_real;
	int		i;

	tmp_real = 0;
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
			color = calc_mandelbrot(&cmplx);
			if (color >= 20 && color < 40)
				put_pixel(&fractol->data, x, y, pixel_color(255, 0, 0, 255));
			else if (color >= 40 && color < 70)
				put_pixel(&fractol->data, x, y, pixel_color(0, 0, 255, 255));
			else if (color >= 70 && color < 100)
				put_pixel(&fractol->data, x, y, pixel_color(0, 255, 255, 255));
			else if (color >= 100 && color < 200)
				put_pixel(&fractol->data, x, y, pixel_color(255, 255, 0, 255));
			else if (color == 200)
				put_pixel(&fractol->data, x, y, pixel_color(255, 0, 255, 255));
			else
				put_pixel(&fractol->data, x, y, pixel_color(0, 0, 0, 255));
			x++;
		}
		y++;
		x = 0;
	}
}

int	calc_julia(t_cmplx *cmplx, char **argv)
{
	float	sum;
	int		i;

	sum = 0;
	i = 0;
	cmplx->creal = to_float(argv[2]);
	cmplx->ci = to_float(argv[3]);
	while (i < 10)
	{
		
	}
}

void	julia(t_fractol *fractol, char **argv)
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
			render_pixel(x, y, &cmplx);
			color = calc_julia(&cmplx, argv);
		}
	}

}

int	keyhooks(int keysym, t_fractol *fractol)
{
	if (keysym == 65307)
		free_exit(fractol);
	return (0);
}

void	fractol(int argc, char **argv)
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
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		mandelbrot(&fractol);
	else
		julia(&fractol, argv);
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.data.img, 0, 0);
	mlx_key_hook(fractol.win, keyhooks, &fractol);
	mlx_loop(fractol.mlx);
	free_exit(&fractol);
}

bool	is_float(char *str)
{
	int	i;
	int	sign;
	int	point;

	i = 0;
	sign = 1;
	point = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		point = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '.' && i == 1 && point == 0)
			i++;
		else if (str[i] == '.' && i == 2 && point == 1)
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (false);
	}
	return (true);
}

// int	to_float()

int	main(int argc, char *argv[])
{
	if ((argc == 2) && ft_strncmp(argv[1], "mandelbrot", 11) == 0)
	{
		printf("mandelbrot succes\n");
		fractol(argc, argv);
	}
	else if ((argc == 2) && ft_strncmp(argv[1], "julia", 6) == 0)
	{
		printf ("only julia\n");
		fractol(argc, argv);
	}
	else if ((argc == 4) && (ft_strncmp(argv[1], "julia", 6) == 0) &&
		is_float(argv[2]) && is_float(argv[3]))
		{
			printf("julia with two succesfull floats\n");
			fractol(argc, argv);
		}
	else if ((argc == 4) && (ft_strncmp(argv[1], "julia", 6) == 0) &&
		!is_float(argv[2]) && !is_float(argv[3]))
		{
			printf("julia but invalid floats\n");
		}
	else
		available_params();
	return (0);
	}
