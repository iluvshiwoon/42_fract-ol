/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/04 18:55:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int close_win(t_vars *vars) {
  mlx_destroy_window(vars->mlx, vars->win);
  mlx_destroy_display(vars->mlx);
  free(vars);
  exit(0);
}

double scale(char axe, double x, t_vars *vars) {
  if (axe == 'w')
    return ((((vars->max_r - vars->min_r) * (x - 0)) / (vars->view_width - 0) +
             vars->min_r));
  else if (axe == 'h')
    return ((((vars->max_i - vars->min_i) * (x - 0)) / (vars->view_height - 0) +
             vars->min_i));
  return 0;
}
