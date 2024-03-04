/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:08:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 17:09:35 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int main(void) {
  t_vars *vars;

  vars = malloc(sizeof(*vars));
  vars->view_width = 1920 / 2;
  vars->view_height = 1080 / 2;
  vars->min_r = -4.0;
  vars->max_r = 4.0;
  vars->min_i = -2.23;
  vars->max_i = 4.0;
  vars->zoom = 1;
  vars->offset_x = 0;
  vars->offset_y = 0;
    vars->center_i = 0;
    vars->center_r = 0;

  printf("%f\n", scale('w', 0., vars));
  printf("%f\n", scale('w', 1., vars));
  printf("%f\n", scale('w', vars->view_width, vars));

  printf("%f\n", scale('h', 0., vars));
  printf("%f\n", scale('h', 1., vars));
  printf("%f\n", scale('h', vars->view_height, vars));

  vars->mlx = mlx_init();
  mlx_do_key_autorepeaton(vars->mlx);

  vars->win = mlx_new_window(vars->mlx, vars->view_width, vars->view_height,
                             "Fract-ol");

  calc_mandelbrot(vars);
  mlx_hook(vars->win, KeyPress, KeyPressMask, &key_events, vars);
  // mlx_hook(vars->win, KeyRelease, KeyReleaseMask, &key_released, vars);
  mlx_hook(vars->win, DestroyNotify, 0, &close_win, vars);
  mlx_loop(vars->mlx);
}
