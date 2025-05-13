/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kehooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:09:58 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/07 16:10:04 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

//prints message when pressing key
int	key_hook(int keycode, t_vars *vars)
{
	(void)keycode;
	(void)vars;
	printf("Hello from key_hook!\n");
	return (0);
}

int	mouse_hook(int button, int x, int y, void(*param))
{
	t_vars	*vars;
	vars = (void *)param;
	if (button == 1) // Left click
		printf("Left click at (%d, %d)\n", x, y);
	if (button == 3)//right click
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit (0);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	free(vars.mlx);
	return (0);
}
