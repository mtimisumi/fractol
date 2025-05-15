/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:07:47 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/15 15:29:30 by mmisumi          ###   ########.fr       */
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

# define WIDTH 2000
# define HEIGHT 1000
# define ITERS 62
# define MANDELBROT 0
# define JULIA 1
# define MAX_COLORS 5 

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_data;

typedef struct	s_cmplx
{
	float	zreal;
	float	zi;
	float	creal;
	float	ci;
}				t_cmplx;

typedef struct	s_pix
{
	float	width;
	float	height;
	float	x_min;
	float	x_max;
	float	y_max;
	float	y_min;
}				t_pix;

typedef struct s_fractol
{
	int			fractol;
	void		*mlx;
	void		*win;
	t_data		data;
	t_pix		pix;
	float		julia_real;
	float		julia_i;
	uint32_t	palette[MAX_COLORS];
}				t_fractol;

void		init_palette(uint32_t *palette);
void		fractol(int argc, char **argv);
void		mandelbrot(t_fractol *fractol);
void		julia(t_fractol *fractol);
bool		is_julia_coordinate(char *str);
float		to_float(char *str);
int			click(int button, int px, int py, t_fractol *fractol);
void		zoomin(int keysym, t_fractol *fractol);
int			close_window(t_fractol *fractol);
int			keyhooks(int keysym, t_fractol *fractol);
void		render_pixel(int x, int y, t_cmplx *cmplx, t_pix *pix);
void		init_pix(t_pix *pix);
__uint32_t	pixel_color(__uint32_t red, __uint32_t green, __uint32_t blue, __uint32_t alpha);
void		put_pixel(t_data *data, int x, int y, int color);
void		free_exit(t_fractol *fractol);

#endif
