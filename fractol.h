/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:07:47 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/16 14:17:20 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include <stdio.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <math.h>
# include <stdint.h>

# define WIDTH 1500
# define HEIGHT 1200
# define ITERS 100
# define MANDELBROT 0
# define JULIA 1
# define MAX_COLORS 5

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}			t_data;

typedef struct s_cmplx
{
	float	zreal;
	float	zi;
	float	creal;
	float	ci;
}			t_cmplx;

typedef struct s_pix
{
	float	width;
	float	height;
	float	x_min;
	float	x_max;
	float	y_max;
	float	y_min;
}			t_pix;

typedef struct s_fract
{
	int			fractol;
	void		*mlx;
	void		*win;
	t_data		data;
	t_pix		pix;
	float		julia_real;
	float		julia_i;
}				t_fract;

int		main(int argc, char *argv[]);
void	init_julia(int argc, char **argv, t_fract *fract);
void	available_params(void);
void	free_exit(t_fract *fract);

bool	is_julia_coordinate(char *str);
float	to_float(char *str);
float	decimals(char *str);

void	create_fractol(t_fract *fract);
void	julia(t_fract *fract);
void	mandelbrot(t_fract *fract);
int		calc_fractol(t_cmplx *cmplx);

int		keyhooks(int keysym, t_fract *fract);
int		mouse(int button, int x, int y, t_fract *fract);
int		close_window(t_fract *fract);
void	put_image(t_fract *fract);
void	click(int button, int px, int py, t_fract *fract);
void	scroll(int button, t_fract *fract);
void	move(int keysym, t_fract *fract);

int		pixel_color(int red, int green, int blue, int alpha);
void	init_palette(uint32_t *palette);
void	put_pixel(t_data *data, int x, int y, int color);
void	init_pix(t_pix *pix);
void	render_pixel(int x, int y, t_cmplx *cmplx, t_pix *pix);

#endif
