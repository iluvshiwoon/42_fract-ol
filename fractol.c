/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:08:57 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/09 18:23:24 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include "X11/X.h"

static void init(t_vars *vars) {
  vars->view_width = VW;
  vars->view_height = VH;
  vars->min_r = -4.0;
  vars->max_r = 4.0;
  vars->min_i = -2.23;
  vars->max_i = 4.0;
  vars->offset_x = 0;
  vars->offset_y = 0;
  vars->zoom = 2;
  vars->cr = 0.285;
  vars->ci = 0.01;
  vars->mouse_x = 0;
  vars->mouse_y = 0;
}

static void print_help(void) {
  ft_printf(
      "  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  "
      "/\\_/\\ "
      " /\\_/\\  /\\_/\\ \n ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( "
      "o.o )( o.o )( o.o )\n  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  "
      "> ^ <  > ^ <  > ^ < \n  /\\_/\\                                         "
      " "
      "                /\\_/\\ \n ( o.o )        __                     _      "
      " "
      "    _   _        ( o.o ) \n  > ^ <        / _|  _ _   __ _   __  | |_   "
      "___  ( ) | |        > ^ < \n  /\\_/\\       |  _| | '_| / _` | / _| |  "
      "_| / _ \\ |/  | |        /\\_/\\ \n ( o.o )      |_|   |_|   \\__,_| "
      "\\__|  \\__| \\___/     |_|       ( o.o )\n  > ^ <                      "
      " "
      "                                   > ^ < \n  /\\_/\\  /\\_/\\  /\\_/\\  "
      "/\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\ \n ( o.o "
      ")( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )\n  > ^ "
      "<  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ < \n\n");
  ft_printf(
      "                            .-----------.\n                --------"
      "----|  "
      " Usage   |------------\n                            '-----------'\n\n");

  ft_printf("                      ./fractol <set> <options>\n\n");
  ft_printf(
      "                              .--------.\n                  -------"
      "-----|  "
      "Sets  |------------\n                              '--------'\n\n");
  ft_printf(
      "                          'M' : Mandelbrot\n                       "
      "   'J' : Julia\n                          'B' : "
      "Burning Ship\n\n");
  ft_printf(
      "                            .-------------.\n                --------"
      "----|  "
      " Options   |------------\n                            "
      "'-------------'\n\n");
  ft_printf("        For Julia set complexe value ranging from -1 - i "
            "to 1 + i\n\n");
  ft_printf("                      Ex : ./fractol J -0.8 0.156\n\n");
}

static void help(t_vars *vars) {
  print_help();
  free(vars);
  exit(0);
}

#include <stdio.h>
static void parse_julia(t_vars *vars, int argc, char **argv) {
  double rvalue;
  int status;
  char *cr;
  char *ci;

  cr = argv[2];
  status = SUCCESS;
  rvalue = atodouble(cr, &status);
  if (status && rvalue <= 1. && rvalue >= -1.)
    vars->cr = rvalue;
  else
    help(vars);
  if (argc == 4) {
    ci = argv[3];
    rvalue = atodouble(ci, &status);
    if (status && rvalue <= 1. && rvalue >= -1.)
      vars->ci = rvalue;
    else
      help(vars);
  } else
    vars->ci = 0;
  vars->type = 'J';
}

static void handle_julia(t_vars *vars, int argc, char **argv) {
  if (argc > 2 && argc < 5)
    parse_julia(vars, argc, argv);
  else
    help(vars);
}

static void parse_input(t_vars *vars, int argc, char **argv) {
  if (argc > 1) {
    if (argv[1][0] == 'M')
      vars->type = 'M';
    else if (argv[1][0] == 'B')
      vars->type = 'B';
    else if (argv[1][0] == 'J')
      handle_julia(vars, argc, argv);
    else
      help(vars);
  } else {
    help(vars);
  }
}

int main(int argc, char **argv) {
  t_vars *vars;

  vars = malloc(sizeof(*vars));
  init(vars);
  parse_input(vars, argc, argv);
  vars->gradient = malloc(sizeof(*(vars->gradient)) * PASS);
  build_palette(vars);

  vars->mlx = mlx_init();
  mlx_do_key_autorepeaton(vars->mlx);
  vars->win = mlx_new_window(vars->mlx, vars->view_width, vars->view_height,
                             "Fract-ol");
  render(vars);
  mlx_hook(vars->win, KeyPress, KeyPressMask, &key_events, vars);
  mlx_mouse_hook(vars->win, &mouse_events, vars);
  mlx_hook(vars->win, DestroyNotify, 0, &close_win, vars);
  mlx_loop(vars->mlx);
}
