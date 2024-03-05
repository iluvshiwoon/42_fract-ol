/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:03:53 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/05 23:28:21 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
#include "42_MyLibC/mylibc.h"
#include "keycode.h"
#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <math.h>
#define VW 1920. / 2
#define VH 1080. / 2
#define PASS 500

typedef struct s_data {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} t_data;

typedef struct s_color {
    int transparency;
    int red;
    int green;
    int blue;
} t_color;

typedef struct s_gradient {
  t_color color1;
  t_color color2;
} t_gradient;

typedef struct s_vars {
  void *mlx;
  void *win;
  int view_width;
  int view_height;

  double min_r;
  double max_r;

  double min_i;
  double max_i;

  int p_x;
  double offset_x;
  int p_y;
  double offset_y;
  double x;
  double y;

  double zoom;
  char direction;

  char type;
  int mouse_x;
  int mouse_y;

  t_gradient gradient;
} t_vars;

// Render
void render(t_vars *vars);
double calc_mandelbrot(t_vars *vars);

// Events
int key_events(int keycode, t_vars *vars);
int mouse_events(int keycode, int x, int y, t_vars *vars);

// Camera
void move(t_vars *vars);

// Utils
int close_win(t_vars *vars);
double scale(char axe, double x, t_vars *vars);

// Mlx Utils
int create_trgb(int t, int r, int g, int b);
void my_mlx_put_pixel(t_data *data, int x, int y, int color);

#endif
