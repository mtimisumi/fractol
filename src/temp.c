/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:26:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/12 12:47:18 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdint.h>

#define WIDTH 1080
#define HEIGHT 850

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}			t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	t_data	data;
}			t_vars;

typedef struct s_complex
{
	float	real;
	float	i;
}			t_complex;

typedef struct s_sum
{
	int			x;
	int			y;
	t_complex	c;
	t_complex	z;
}				t_sum;




void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	printf("x: %d\n", x);
	printf("y: %d\n", y);
	float new_x = render_pixel(x, -2.5, 1.5, WIDTH);
	float new_y = render_pixel(y, 1.5, -1.5, HEIGHT);
	printf("new_x: %d\n", new_x);
	printf("new_y: %d\n", new_y);

	// dst = data->addr + (new_y * data->len + new_x * (data->bpp / 8));
	// *(unsigned int*)dst = color;
}

void	calc_point(t_vars *vars, t_sum *sum)
{
	(void)vars;
	float		tmp_real;
	int	add = 0;
	
	//first iteration always starts at (0, 0)
	
	//our random point
	
	for (int i = 0; i < 5; ++i)
	{
		//z^2
		tmp_real = (sum->z.real * sum->z.real) - (sum->z.i * sum->z.i);
		sum->z.i = (2 * sum->z.real) * sum->z.i;
		sum->z.real = tmp_real;
		
		//z^2 + c
		sum->z.real += sum->c.real;
		sum->z.i += sum->c.i;
		
		add = sum->z.real + sum->z.i;
		if (add > 2)
		{
			my_mlx_pixel_put(&vars->data, 400, 600, ft_pixel(255, 255, 0, 255));
			return ;
		}
		// printf("iteration i: %d\treal: %f\timaginary: %f\n", i, z.real, z.i);
	}
	if (add < 2)
	my_mlx_pixel_put(&vars->data, 400, 600, ft_pixel(255, 255, 255, 255));
	return ;
}

float	render_pixel(float x, float new_min, float new_max, float old_max)
{
	float	new_x = (x / old_max);
	float	new_pos = (new_x * (new_max - new_min));
	return (new_pos + new_min);
}

int	mouse_hook(int button, int x, int y, void(*param))
{
	t_vars	*vars;
	vars = (void *)param;
	float new_x = render_pixel(x, -2.5, 1.5, WIDTH);
	float new_y = render_pixel(y, 1.5, -1.5, HEIGHT);
	if (button == 1) // Left click
	printf("Left click at (%f, %f)\n", new_x, new_y);
	if (button == 3)//right click
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free_exit(vars);
	}
	return (0);
}

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// int	my_mlx_key_hook(int keysym, t_vars *vars)
// {
	// 	if (keysym == XK_Escape)
	// 	{
		// 		mlx_destroy_display(vars->mlx);
		// 		free(vars->win);
		// 		free(vars->mlx);
		// 		free(vars->data.img);
		// 		free(vars->data.addr);
		// 		exit (1);
		// 	}
		
		
		int	close_window(t_vars *vars)
		{
			printf("ADsadsadsadsad\n");
			mlx_destroy_display(vars->mlx);
			mlx_destroy_window(vars->mlx, vars->win);
			free(vars->win);
			free(vars->mlx);
			exit(1);
		}
		
		void	mandelbrot(t_vars *vars)
		{
			t_sum	sum;
			
			sum.x = 0;
			sum.y = 0;
			sum.c.real = 0;
			sum.c.i = 0;
			sum.z.real = 0;
			sum.z.i = 0;
			int x = 0;
			int	y = 0;
			while (y < HEIGHT)
			{
				while (x < WIDTH)
				{
					sum.
			calc_point(vars, &sum);
			x++;
		}
		y++;
	}
}

void	free_exit(t_vars *vars)
{

	void	free_exit(t_vars *vars)
	{
		if (vars->mlx)
			free(vars->mlx);
		if (vars->win)
			free(vars->win);
		if (vars->data.img)
			free(vars->data.img);
		if (vars->data.addr)
			free(vars->data.addr);
		free(vars);
		exit (2);
	}	if (vars->data.addr)
		free(vars->data.addr);
	free(vars);
	exit (2);
}

void	fractol()
{
	t_vars	vars;
	float	x;
	float	y;
	
	x = 0;
	y = 0;
	
	vars.mlx = mlx_init();
	if (!vars.mlx)
	return (free_exit(&vars));
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "mandelbrot");
	if (!vars.win)
	return (free_exit(&vars));
	vars.data.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.data.img)
	return (free_exit(&vars));
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bpp, &vars.data.len, &vars.data.endian);
	if (!vars.data.addr)
	return (free_exit(&vars));
	// int color = 431
	// mlx_hook(my_display->win, ON_DESTROY, 0L, close_on_event, my_display);
	// get_point();

	//17 is event for window close
	// mlx_key_hook(vars.win, my_mlx_key_hook, &vars);
	// calc_point();
	// mlx_hook(&vars.win, 17, (1L<<12), close_window, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mandelbrot(&vars);
	// my_mlx_pixel_put(&vars.data, 400, 600, ft_pixel(255, 255, 0, 255));
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_loop(vars.mlx);
	return ;
}

int	main(void)
{
	fractol();
	return (0);
}