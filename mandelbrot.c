/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:14:42 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/05 10:58:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	calc_mandelbrot(t_vars *vars)
{
	int		i;
	double	zr;
	double	zi;
	double	zr_temp;

	i = 0;
	zr = 0.0;
	zi = 0.0;
	while (i < PASS)
	{
		zr_temp = zr * zr - zi * zi + vars->x;
		zi = 2 * zr * zi + vars->y;
		zr = zr_temp;
		if (zr * zr + zi * zi > 4)
			break ;
		++i;
	}
	return (i);
}
