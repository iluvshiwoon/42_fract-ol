/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:16:35 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 17:23:43 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int move(t_vars *vars) {
  double center_r;
  double center_i;

  vars->center_r = center(vars->max_r, vars->min_r);
  vars->center_i = center(vars->max_i, vars->min_i);

  if (vars->is_pressed) {
    if (vars->direction == 'D')
      vars->offset_x += 4 * vars->zoom;
    else if (vars->direction == 'A')
      vars->offset_x -= 4 * vars->zoom;
    else if (vars->direction == 'W')
      vars->offset_y -= 4 * vars->zoom;
    else if (vars->direction == 'S')
      vars->offset_y += 4 * vars->zoom;
    else if (vars->direction == '+') {
      vars->zoom = 0.5;
      vars->min_r = vars->min_r * vars->zoom;
      vars->max_r = vars->max_r * vars->zoom;
      vars->min_i = vars->min_i * vars->zoom;
      vars->max_i = vars->max_i * vars->zoom;
           vars->offset_x/=vars->zoom;
           vars->offset_y/=vars->zoom;
    } else if (vars->direction == '-') {
      vars->zoom = 2;
           vars->offset_y/=vars->zoom;
           vars->offset_x/=vars->zoom;
      vars->min_r = vars->min_r * vars->zoom;
      vars->max_r = vars->max_r * vars->zoom;
      vars->min_i = vars->min_i * vars->zoom;
      vars->max_i = vars->max_i * vars->zoom;
    }
        // recenter(center_r,center_i,vars);
  // center_r = center(vars->max_r, vars->min_r);
  // center_i = center(vars->max_i, vars->min_i);

    return 1;
  }
  return 0;
}
