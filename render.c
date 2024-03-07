/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:16:12 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/07 15:18:33 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int calc_pixel_color_multiplier(t_vars *vars) {
  if (vars->type == 'M')
    return (calc_mandelbrot(vars));
  else if (vars->type == 'B')
    return (calc_burning_ship(vars));
  return 0;
}

static void put_pixel(t_vars *vars, t_data *img) {
  t_color color;
  int i;

  i = calc_pixel_color_multiplier(vars);
  get_color(i, vars->gradient, &color);
  my_mlx_put_pixel(img, vars->p_x, vars->p_y,
                   create_trgb(color.transparency * (i < PASS),
                               color.red * (i < PASS), color.green * (i < PASS),
                               color.blue * (i < PASS)));
}

void render(t_vars *vars) {
  t_data img;
  double increment;
  double y_origin;

  vars->p_x = 0;
  vars->x = scale('w', vars->offset_x, vars);
  y_origin = scale('h', vars->offset_y, vars);

  img.img = mlx_new_image(vars->mlx, VW, VH);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  increment = scale('w', 1., vars) - scale('w', 0., vars);
  while (vars->p_x < VW) {
    vars->p_y = 0;
    vars->y = y_origin;
    while (vars->p_y < VH) {
      put_pixel(vars, &img);
      ++(vars->p_y);
      vars->y += increment;
    }
    ++(vars->p_x);
    vars->x += increment;
  }
  mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
  mlx_destroy_image(vars->mlx, img.img);
}
