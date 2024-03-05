/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:08:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/06 00:25:45 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include "X11/X.h"

int main(void) {
  t_vars *vars;

  vars = malloc(sizeof(*vars));
  vars->view_width = VW;
  vars->view_height = VH;
  vars->min_r = -4.0;
  vars->max_r = 4.0;
  vars->min_i = -2.23;
  vars->max_i = 4.0;
  vars->offset_x = 0;
  vars->offset_y = 0;
  vars->zoom = 2;
  vars->type = 'M';
  vars->mouse_x = 0;
  vars->mouse_y = 0;
  // vars->gradient.color1.red = 14;
  // vars->gradient.color1.green = 13;
  // vars->gradient.color1.blue = 148;
  // vars->gradient.color1.transparency = 247;
  //
  // vars->gradient.color2.red = 255;
  // vars->gradient.color2.green =249;
  // vars->gradient.color2.blue = 145;
  // vars->gradient.color2.transparency = 247;
  vars->gradient = malloc(sizeof(*(vars->gradient)) * PASS);
  build_palette(vars);

  vars->mlx = mlx_init();
  mlx_do_key_autorepeaton(vars->mlx);
  vars->win = mlx_new_window(vars->mlx, vars->view_width, vars->view_height,
                             "Fract-ol");
  render(vars);
  mlx_hook(vars->win, KeyPress, KeyPressMask, &key_events, vars);
  mlx_mouse_hook(vars->win, &mouse_events, vars);
  // mlx_hook(vars->win, ButtonPress, ButtonPressMask, &mouse_events,
  //          vars);
  mlx_hook(vars->win, DestroyNotify, 0, &close_win, vars);
  mlx_loop(vars->mlx);
}
