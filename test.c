/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/03 20:45:17 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keycode.h"

#include <X11/X.h>
#include <stdio.h>
void my_mlx_put_pixel(t_data *data, int x, int y, int color) {
  char *dst;
  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int *)dst = color;
}

int create_trgb(int t, int r, int g, int b) {
  return (t << 24 | r << 16 | g << 8 | b);
}

int key_released(int keycode, t_vars *vars) {
  printf("RELEASED:%d\n", keycode);
  if (keycode == KEY_D)
    vars->is_pressed = 0;
  else if (keycode == KEY_A)
    vars->is_pressed = 0;
  else if (keycode == KEY_W)
    vars->is_pressed = 0;
  else if (keycode == KEY_S)
    vars->is_pressed = 0;
  else
    return 0;
  return 1;
}

double center(double max, double min) {
  if (max >= 0 && min <= 0)
    return (max + min);
  else
    return ((max + min) / 2);
}

void recenter(double center_r,double center_i, t_vars * vars)
{
    double new_center_r;
    double new_center_i;

    new_center_r = center(vars->max_r, vars->min_r);
    new_center_i = center(vars->max_i, vars->min_i);

 printf("R %f %f %f\n I %f %f %f\n", vars->min_r, new_center_r, vars->max_r,
         vars->min_i, new_center_i, vars->max_i);


    if (center_r <= new_center_r)
    {
        vars->offset_x -= (new_center_r - center_r)/scale('w', 1., vars);
    }
    else if (center_r > new_center_r)
    {
        vars->offset_x += (-new_center_r + center_r)/scale('w', 1., vars);
    }
    if (center_i <= new_center_i)
    {
        vars->offset_y -= (new_center_i - center_i)/scale('w', 1., vars);
    }
    else if (center_i > new_center_i)
    {
        vars->offset_y += (-new_center_i + center_i)/scale('w', 1., vars);
    }
}
int move(t_vars *vars) {
  double center_r;
  double center_i;

  vars->center_r = center(vars->max_r, vars->min_r);
  vars->center_i = center(vars->max_i, vars->min_i);
  printf("R %f %f %f\n I %f %f %f\n", vars->min_r, center_r, vars->max_r,
         vars->min_i, center_i, vars->max_i);

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
    } else if (vars->direction == '-') {
      vars->zoom = 2;
      vars->min_r = vars->min_r * vars->zoom;
      vars->max_r = vars->max_r * vars->zoom;
      vars->min_i = vars->min_i * vars->zoom;
      vars->max_i = vars->max_i * vars->zoom;
    }
        // recenter(center_r,center_i,vars);
  center_r = center(vars->max_r, vars->min_r);
  center_i = center(vars->max_i, vars->min_i);

    printf("R %f %f %f\n I %f %f %f\n", vars->min_r, center_r, vars->max_r,
           vars->min_i, center_i, vars->max_i);

    return 1;
  }
  return 0;
}

void set_key_pressed(t_vars *vars, char direction) {
  vars->is_pressed = 1;
  vars->direction = direction;
  move(vars);
  calc_mandelbrot(vars);
}

int key_events(int keycode, t_vars *vars) {
  printf("%d\n", keycode);
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
  else
    return (0);
  return 1;
}

int close_win(t_vars *vars) {
  mlx_destroy_window(vars->mlx, vars->win);
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

int render(t_vars *vars) {
  printf("called");
  if (move(vars))
    calc_mandelbrot(vars);
  return 1;
}

int calc_mandelbrot(t_vars *vars) {
  t_data img;
  int i;
  double zr;
  double zi;
  double zr_temp;

  vars->p_x = 0;
  vars->x = scale('w', vars->center_r + vars->offset_x, vars);

  img.img = mlx_new_image(vars->mlx, VW, VH);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  while (vars->p_x < VW) {
    vars->p_y = 0;
    vars->y = scale('h', vars->center_i + vars->offset_y, vars);
    while (vars->p_y < VH) {
      i = 0;
      zr = 0.0;
      zi = 0.0;
      while (i < PASS) {
        zr_temp = zr * zr - zi * zi + vars->x;
        zi = 2 * zr * zi + vars->y;
        zr = zr_temp;
        if (zr * zr + zi * zi > 4)
          break;
        ++i;
      }
      my_mlx_put_pixel(&img, vars->p_x, vars->p_y,
                       create_trgb((5 * i + 30) % 255, (10 * i + 30) % 255,
                                   (20 * i + 30) % 255, (30 * i + 30) % 255));
      ++(vars->p_y);
      vars->y += scale('w', 1., vars) - scale('w', 0., vars);
    }
    ++(vars->p_x);
    vars->x += scale('w', 1., vars) - scale('w', 0., vars);
  }
  mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
  return 1;
}

int main(void) {
  t_vars *vars;

  vars = malloc(sizeof(*vars));
  vars->view_width = 1920 / 2;
  vars->view_height = 1080 / 2;
  vars->min_r = -4.0;
  vars->max_r = 4.0;
  vars->min_i = -2.23;
  vars->max_i = 4.0;
  vars->zoom = 1;
  vars->offset_x = 0;
  vars->offset_y = 0;
    vars->center_i = 0;
    vars->center_r = 0;

  printf("%f\n", scale('w', 0., vars));
  printf("%f\n", scale('w', 1., vars));
  printf("%f\n", scale('w', vars->view_width, vars));

  printf("%f\n", scale('h', 0., vars));
  printf("%f\n", scale('h', 1., vars));
  printf("%f\n", scale('h', vars->view_height, vars));

  vars->mlx = mlx_init();
  mlx_do_key_autorepeaton(vars->mlx);

  vars->win = mlx_new_window(vars->mlx, vars->view_width, vars->view_height,
                             "Fract-ol");

  calc_mandelbrot(vars);
  mlx_hook(vars->win, KeyPress, KeyPressMask, &key_events, vars);
  // mlx_hook(vars->win, KeyRelease, KeyReleaseMask, &key_released, vars);
  mlx_hook(vars->win, DestroyNotify, 0, &close_win, vars);
  mlx_loop(vars->mlx);
}
