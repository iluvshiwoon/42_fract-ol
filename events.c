/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 19:58:54 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void set_key_pressed(t_vars *vars, char direction) {
  vars->direction = direction;
  move(vars);
  render(vars);
}

int key_events(int keycode, t_vars *vars) {
  if (keycode == KEY_ESC) {
    close_win(vars);
  } else if (keycode == KEY_D || keycode == KEY_RIGHT)
    set_key_pressed(vars, 'D');
  else if (keycode == KEY_A || keycode == KEY_LEFT)
    set_key_pressed(vars, 'A');
  else if (keycode == KEY_W || keycode == KEY_UP)
    set_key_pressed(vars, 'W');
  else if (keycode == KEY_S || keycode == KEY_DOWN)
    set_key_pressed(vars, 'S');
  else if (keycode == KEY_PLUS)
    set_key_pressed(vars, '+');
  else if (keycode == KEY_MINUS)
    set_key_pressed(vars, '-');
  return 1;
}
