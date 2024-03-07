/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:20:27 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/07 15:20:52 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double abs_double(double a)
{
    if (a < 0)
        return (-a);
    return (a);
}

int calc_burning_ship(t_vars *vars) {
  int i;
  double zr;
  double zi;
  double zr_temp;

  i = 0;
  zr = 0.0;
  zi = 0.0;
  while (i < PASS) {
    zr = abs_double(zr);
    zi = abs_double(zi);
    zr_temp = zr * zr - zi * zi + vars->x;
    zi = 2 * zr * zi + vars->y;
    zr = zr_temp;
    if (zr * zr + zi * zi > 4)
      break;
    ++i;
  }
  return i;
}
