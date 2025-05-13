/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:40:57 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/09 13:03:38 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


typedef struct s_complex
{
	float	real;
	float	i;
}				t_complex;


void	mandelbrot()
{
	
}

//f(z) = z^2 + c
//(x + yi)^2 = x^2 - y^2 + 2xyi
//real = x^2 - y^2
//i = 2xyi

int	main()
{
	t_complex	z;
	t_complex	c;
	float		tmp_real;

	//first iteration always starts at (0, 0)
	z.real = 0;
	z.i = 0;

	//our random point
	c.real = -0.2;
	c.i =0.13;

	for (int i = 0; i < 42; ++i)
	{
		//z^2
		tmp_real = (z.real * z.real) - (z.i * z.i);
		z.i = (2 * z.real) * z.i;
		z.real = tmp_real;

		//z^2 + c
		z.real += c.real;
		z.i += c.i;

		printf("iteration i: %d\treal: %f\timaginary: %f\n", i, z.real, z.i);
	}
	mandelbrot();
}