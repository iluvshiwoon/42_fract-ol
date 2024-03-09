/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:19:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/09 21:41:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int close_win(t_vars *vars) {
  mlx_destroy_window(vars->mlx, vars->win);
  mlx_destroy_display(vars->mlx);
  free(vars->mlx);
  free(vars->gradient);
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

static double get_sign(char c, size_t *i) {
  double sign;
  if (c == '-')
    sign = -1.;
  else
    sign = 1.;
  if (c == '-' || c == '+')
    ++(*i);
  return (sign);
}
double atodouble(char *string, int *status) {
  size_t i[2];
  double sign;
  double r_value;
  double floating_point;

  i[0] = 0;
  i[1] = 1;
  r_value = 0.;
  floating_point = 0.;
  sign = get_sign(string[i[0]], &(i[0]));
  while (ft_isdigit(string[i[0]]) && string[i[0]]) {
    r_value = r_value * 10 + string[i[0]] - '0';
    ++(i[0]);
  }
  if (i[0] && string[i[0]] && string[i[0]] == '.') {
    ++(i[0]);
    while (ft_isdigit(string[i[0]]) && string[i[0]]) {
      floating_point =
          floating_point + (string[i[0]++] - '0') / pow(10.,i[1]++);
    }
  }
  if (string[i[0]])
    *status = ERROR;
  return (sign * (r_value + floating_point));
}
