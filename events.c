/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 17:22:02 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int key_released(int keycode, t_vars *vars) {
  if (keycode == KEY_D)
    vars->is_pressed = 0;
  else if (keycode == KEY_A)
    vars->is_pressed = 0;
  else if (keycode == KEY_W)
    vars->is_pressed = 0;
  else if (keycode == KEY_S)
    vars->is_pressed = 0;
  else
    return 0;
  return 1;
}

double center(double max, double min) {
  if (max >= 0 && min <= 0)
    return (max + min);
  else
    return ((max + min) / 2);
}

void recenter(double center_r, double center_i, t_vars *vars) {
  double new_center_r;
  double new_center_i;

  new_center_r = center(vars->max_r, vars->min_r);
  new_center_i = center(vars->max_i, vars->min_i);

  if (center_r <= new_center_r) {
    vars->offset_x -= (new_center_r - center_r) / scale('w', 1., vars);
  } else if (center_r > new_center_r) {
    vars->offset_x += (-new_center_r + center_r) / scale('w', 1., vars);
  }
  if (center_i <= new_center_i) {
    vars->offset_y -= (new_center_i - center_i) / scale('w', 1., vars);
  } else if (center_i > new_center_i) {
    vars->offset_y += (-new_center_i + center_i) / scale('w', 1., vars);
  }
}

void set_key_pressed(t_vars *vars, char direction) {
  vars->is_pressed = 1;
  vars->direction = direction;
  move(vars);
  calc_mandelbrot(vars);
}

int key_events(int keycode, t_vars *vars) {
  if (keycode == KEY_ESC) {
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
  } else if (keycode == KEY_D)
    set_key_pressed(vars, 'D');
  else if (keycode == KEY_A)
    set_key_pressed(vars, 'A');
  else if (keycode == KEY_W)
    set_key_pressed(vars, 'W');
  else if (keycode == KEY_S)
    set_key_pressed(vars, 'S');
  else if (keycode == KEY_PLUS)
    set_key_pressed(vars, '+');
  else if (keycode == KEY_MINUS)
    set_key_pressed(vars, '-');
  else
    return (0);
  return 1;
}
