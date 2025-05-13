/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:10:11 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/07 16:10:20 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		x_pos;
}			t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	int		x;
	int		running;
}	t_vars;

int	close_it(int keycode, t_vars *vars)
{
	(void)keycode;
	mlx_destroy_window(vars->mlx, vars->win);//frees window
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars);
	exit(0);
	return (0);
}

int	render_next_frame(void *param)
{
	t_vars	*vars;
	vars = (t_vars *)param;
	if (!vars->running)
		return (0);
	//clear previous frame
	mlx_clear_window(vars->mlx, vars->win);
	//draws a single red line at (x_pos, 100)
	mlx_pixel_put(vars->mlx, vars->win, vars->x, 100, 0xFFFFFF);
	vars->x += 5;
	if (vars->x > 640)
		vars->x = 0;
	usleep(16000);
	return (0);
}

int	main(void)
{
	t_vars *vars = malloc(sizeof(t_vars));
	if (!vars)
		return (1);
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		free(vars);
		return (1);
	}
	vars->win = mlx_new_window(vars->mlx, 640, 480, "Hello!");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free(vars);
		return (1);
	}
	vars->x = 0;
	vars->running = 1;
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_hook(vars->win, 2, 1L << 0, close_it, vars);
	mlx_loop(vars->mlx);
	return (0);
}
