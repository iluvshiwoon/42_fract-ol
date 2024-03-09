/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:14:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/09 21:44:24 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void shift_color(t_vars *vars, char direction) {
  if (direction == 'K') {
    vars->color_multiplier[0]++;
    vars->color_multiplier[1]++;
    vars->color_multiplier[2]++;
    vars->color_multiplier[3]++;
  } else if (direction == 'J') {
    vars->color_multiplier[0]--;
    vars->color_multiplier[1]--;
    vars->color_multiplier[2]--;
    vars->color_multiplier[3]--;
  }
}

void build_palette(t_vars *vars) {
  int i;

  i = 0;
  while (i < PASS) {
    vars->gradient[i].transparency = (vars->color_multiplier[0] * (int)i) % 255;
    vars->gradient[i].red = (vars->color_multiplier[1] * (int)i) % 255;
    vars->gradient[i].green = (vars->color_multiplier[2] * (int)i) % 255;
    vars->gradient[i].blue = (vars->color_multiplier[3] * (int)i) % 255;
    ++i;
  }
}

t_color *get_color(int i, t_color *gradient, t_color *color) {
  double i_scaled;

  if (i == PASS)
    i -= 2;
  else if (i == PASS - 1)
    i -= 1;
  i_scaled = (double)i / PASS;
  color->transparency =
      gradient[i].transparency +
      i_scaled * (gradient[i + 1].transparency - gradient[i].transparency);
  color->red =
      gradient[i].red + i_scaled * (gradient[i + 1].red - gradient[i].red);
  color->green = gradient[i].green +
                 i_scaled * (gradient[i + 1].green - gradient[i].green);
  color->blue =
      gradient[i].blue + i_scaled * (gradient[i + 1].blue - gradient[i].blue);
  return color;
}
