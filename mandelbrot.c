/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:14:42 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/05 23:55:58 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

static double calc_pixel_color_multiplier(t_vars *vars) {
  if (vars->type == 'M')
    return (calc_mandelbrot(vars));
  return 0;
}

#include <stdio.h>
t_color *get_color(double i, t_gradient gradient, t_color *color) {
  double i_scaled;

  i_scaled = (double)i / PASS;
  // i_scaled = 1 - i_scaled;
  color->transparency =
      gradient.color1.transparency +
      i_scaled * (gradient.color2.transparency - gradient.color1.transparency);
  color->red = gradient.color1.red +
               i_scaled * (gradient.color2.red - gradient.color1.red);
  color->green = gradient.color1.green +
                 i_scaled * (gradient.color2.green - gradient.color1.green);
  color->blue = gradient.color1.blue +
                i_scaled * (gradient.color2.blue - gradient.color1.blue);
  return color;
}

void render(t_vars *vars) {
  t_color color;
  t_data img;
  double i;

  vars->p_x = 0;
  vars->x = scale('w', vars->offset_x, vars);

  img.img = mlx_new_image(vars->mlx, VW, VH);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  while (vars->p_x < VW) {
    vars->p_y = 0;
    vars->y = scale('h', vars->offset_y, vars);
    while (vars->p_y < VH) {
      i = calc_pixel_color_multiplier(vars);
      get_color(i, vars->gradient, &color);
      my_mlx_put_pixel(
          &img, vars->p_x, vars->p_y,
          create_trgb(color.transparency * (i < PASS), color.red * (i < PASS),
                      color.green * (i < PASS), color.blue * (i < PASS)));
      // create_trgb((5 * i + 30) % 255, (10 * i + 30) % 255,
      //             (20 * i + 30) % 255, (30 * i + 30) % 255));
      ++(vars->p_y);
      vars->y += scale('w', 1., vars) - scale('w', 0., vars);
    }
    ++(vars->p_x);
    vars->x += scale('w', 1., vars) - scale('w', 0., vars);
  }
  mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
  mlx_destroy_image(vars->mlx, img.img);
}

double max(double a, double b) {
  if (a > b)
    return a;
  return b;
}

double calc_mandelbrot(t_vars *vars) {
  int i;
  double log_zn;
  double smooth;
  double zr;
  double zi;
  double zr_temp;

  i = 0;
  zr = 0.0;
  zi = 0.0;
  while (i < PASS) {
    zr_temp = zr * zr - zi * zi + vars->x;
    zi = 2 * zr * zi + vars->y;
    zr = zr_temp;
    if (zr * zr + zi * zi > 4)
      break;
    ++i;
  }
  log_zn = log(zr * zr + zi * zi) / 2;
  smooth = log(log_zn / log(4)) / log(2);
  smooth = i + 1 - smooth;
  return smooth;
}
