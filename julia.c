/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:27:01 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/05 10:58:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calc_julia(t_vars *vars)
{
	int		i;
	double	zr;
	double	zi;
	double	zr_temp;

	i = 0;
	zr = vars->x;
	zi = vars->y;
	while (i < PASS)
	{
		zr_temp = zr * zr - zi * zi + vars->cr;
		zi = 2 * zr * zi + vars->ci;
		zr = zr_temp;
		if (zr * zr + zi * zi > 4)
			break ;
		++i;
	}
	return (i);
}
