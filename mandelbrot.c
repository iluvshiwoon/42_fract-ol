/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:14:42 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/07 09:58:41 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

static double calc_pixel_color_multiplier(t_vars *vars) {
  if (vars->type == 'M')
    return (calc_mandelbrot(vars));
  return 0;
}

void build_palette(t_vars *vars) {
  int i;

  i = 0;
  while (i < PASS) {
    vars->gradient[i].transparency = (6 * (int)i) % 255;
    vars->gradient[i].red = (8 * (int)i) % 255;
    vars->gradient[i].green = ((int)i) % 255;
    vars->gradient[i].blue = (5 * (int)i) % 255;
    ++i;
  }
}

#include <stdio.h>
t_color *get_color(double i, t_color *gradient, t_color *color) {
  double i_scaled;
  int i_floor;

  i_floor = floor(i);
  if (i_floor == PASS)
    i_floor -= 3;
  else if (i_floor == PASS - 1)
    i_floor -= 2;
  else if (i_floor == PASS - 2)
    i_floor -= 1;
  else if (i_floor < 0)
    i_floor = 0;
  i_scaled = (double)i / PASS;

  color->transparency = gradient[i_floor].transparency +
                        i_scaled * (gradient[i_floor + 1].transparency -
                                    gradient[i_floor].transparency);
  color->red = gradient[i_floor].red +
               i_scaled * (gradient[i_floor + 1].red - gradient[i_floor].red);
  color->green =
      gradient[i_floor].green +
      i_scaled * (gradient[i_floor + 1].green - gradient[i_floor].green);
  color->blue =
      gradient[i_floor].blue +
      i_scaled * (gradient[i_floor + 1].blue - gradient[i_floor].blue);
  return color;
}

void average_color(t_color *color, t_color *averaged, int samples) {
  int i;

  i = 0;
  averaged->transparency = 0;
  averaged->red = 0;
  averaged->blue = 0;
  averaged->green = 0;
  while (i < samples) {
    averaged->transparency += color[i].transparency;
    averaged->red += color[i].red;
    averaged->blue += color[i].blue;
    averaged->green += color[i].green;
    ++i;
  }
  averaged->transparency /= samples;
  averaged->red /= samples;
  averaged->blue /= samples;
  averaged->green /= samples;
}

void render(t_vars *vars) {
  t_color *color;
  t_color averaged;
  t_data img;
  double i;
  int j;

  color = malloc(sizeof(*color) * 16);
  vars->p_x = 0;
  vars->x = scale('w', vars->offset_x, vars);

  img.img = mlx_new_image(vars->mlx, VW, VH);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  while (vars->p_x < VW) {
    vars->p_y = 0;
    vars->y = scale('h', vars->offset_y, vars);
    while (vars->p_y < VH) {
      j = 0;
      while (j < 16) {
        vars->x += (scale('w', 1., vars) - scale('w', 0., vars)) / 16.;
        vars->y += (scale('w', 1., vars) - scale('w', 0., vars)) / 16.;
        i = calc_pixel_color_multiplier(vars);
        get_color(i, vars->gradient, &(color[j]));
        ++j;
      }
      vars->x -= scale('w', 1., vars) - scale('w', 0., vars);
      vars->y -= scale('w', 1., vars) - scale('w', 0., vars);
      average_color(color, &averaged, 16);
      my_mlx_put_pixel(&img, vars->p_x, vars->p_y,
                       create_trgb(averaged.transparency * (i < PASS),
                                   averaged.red * (i < PASS),
                                   averaged.green * (i < PASS),
                                   averaged.blue * (i < PASS)));
      // create_trgb((5 * i + 30) % 255, (10 * i + 30) % 255,
      //             (20 * i + 30) % 255, (30 * i + 30) % 255));
      ++(vars->p_y);
      vars->y += scale('w', 1., vars) - scale('w', 0., vars);
    }
    ++(vars->p_x);
    vars->x += scale('w', 1., vars) - scale('w', 0., vars);
  }
  free(color);
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
  smooth = log(log_zn / log(2)) / log(2);
  smooth = i + 1 - smooth;
  return smooth;
}
