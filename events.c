/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 17:57:10 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void set_key_pressed(t_vars *vars, char direction) {
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
  return 1;
}
