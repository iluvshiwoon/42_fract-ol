/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:16:35 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 17:55:05 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void move(t_vars *vars) {
  if (vars->direction == 'D')
    vars->offset_x += 4 * vars->zoom;
  else if (vars->direction == 'A')
    vars->offset_x -= 4 * vars->zoom;
  else if (vars->direction == 'W')
    vars->offset_y -= 4 * vars->zoom;
  else if (vars->direction == 'S')
    vars->offset_y += 4 * vars->zoom;
  else if (vars->direction == '+') {
    vars->min_r = vars->min_r / vars->zoom;
    vars->max_r = vars->max_r / vars->zoom;
    vars->min_i = vars->min_i / vars->zoom;
    vars->max_i = vars->max_i / vars->zoom;
    vars->offset_x *= vars->zoom;
    vars->offset_y *= vars->zoom;
  } else if (vars->direction == '-') {
    vars->offset_y /= vars->zoom;
    vars->offset_x /= vars->zoom;
    vars->min_r = vars->min_r * vars->zoom;
    vars->max_r = vars->max_r * vars->zoom;
    vars->min_i = vars->min_i * vars->zoom;
    vars->max_i = vars->max_i * vars->zoom;
  }
}
