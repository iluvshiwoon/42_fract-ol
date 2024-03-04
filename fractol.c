/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:08:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 17:37:25 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

static void init(t_vars *vars) {
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
  vars->mlx = mlx_init();
  mlx_do_key_autorepeaton(vars->mlx);
  vars->win = mlx_new_window(vars->mlx, vars->view_width, vars->view_height,
                             "Fract-ol");
}

int main(void) {
  t_vars *vars;

    init(vars);
  calc_mandelbrot(vars);
  mlx_hook(vars->win, KeyPress, KeyPressMask, &key_events, vars);
  mlx_hook(vars->win, DestroyNotify, 0, &close_win, vars);
  mlx_loop(vars->mlx);
}
