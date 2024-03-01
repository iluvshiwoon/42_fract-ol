/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/01 18:42:09 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void my_mlx_put_pixel(t_data *data, int x, int y, int color) {
  char *dst;
  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int *)dst = color;
}

int create_trgb(int t, int r, int g, int b) {
  return (t << 24 | r << 16 | g << 8 | b);
}

#include <stdio.h>
int key_events(int keycode, t_vars *vars) {
  printf("%d\n", keycode);
  if (keycode == KEY_ESC) {
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
  } else if (keycode == KEY_D)
    vars->offset_x += 2. / vars->zoom*10;
  else if (keycode == KEY_A)
    vars->offset_x -= 2. / vars->zoom*10;
  else if (keycode == KEY_W)
    vars->offset_y -= 2. / vars->zoom*10;
  else if (keycode == KEY_S)
    vars->offset_y += 2. / vars->zoom*10;
  else if (keycode == KEY_PLUS)
            vars->zoom += 500;
  else if (keycode == KEY_MINUS)
    vars->zoom -= 500;

  else
    return (0);
  calc_mandelbrot(vars);
  return 1;
}

double scale(double x)
{
    return(((4 - -4) * (x - 0))/(1920 - 0) + -4);
}

int calc_mandelbrot(t_vars *vars) {
  t_data img;
  int i;
  double zr;
  double zi;
  double zr_temp;

  vars->p_x = 0;
  // vars->x = -VW / vars->zoom + vars->offset_x;
    vars->x = scale(0.);

  img.img = mlx_new_image(vars->mlx, VW, VH);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                               &img.endian);
  while (vars->p_x < VW) {
    vars->p_y = 0;
    // vars->y = -VH / vars->zoom + vars->offset_y;
        vars->y = scale(0.);
    while (vars->p_y < VH) {
      i = 0;
      zr = 0.0;
      zi = 0.0;
      while (i < PASS) {
        zr_temp = zr * zr - zi * zi + vars->x;
        zi = 2 * zr * zi + vars->y;
        zr = zr_temp;
        if (zr * zr + zi * zi >= 4)
          break;
        ++i;
      }
      if (i == PASS)
        my_mlx_put_pixel(&img, vars->p_x, vars->p_y, create_trgb(0, 0, 0, 0));
      else
        my_mlx_put_pixel(
            &img, vars->p_x, vars->p_y,
            create_trgb(0, (10 * i) % 255, (20 * i) % 255, (30 * i) % 255));
      ++(vars->p_y);
      // vars->y += 2. / vars->zoom;
            vars->y += scale(1.) - scale(0.);
    }
    ++(vars->p_x);
    // vars->x += 2. / vars->zoom;
        vars->x += scale(1.) - scale(0.);
  }
  mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
  return 1;
}

int main(void) {
  t_vars *vars;

  vars = malloc(sizeof(*vars));
  vars->mlx = mlx_init();
  vars->win = mlx_new_window(vars->mlx, VW, VH, "Mandelbrot");
  vars->zoom = 200;
  vars->offset_x = 0;
  vars->offset_y = 0;
    printf("%lf\n", scale(0.));
    printf("%lf\n", scale(1.));
    printf("%lf\n", scale(1920.));

  calc_mandelbrot(vars);
  mlx_key_hook(vars->win, &key_events, vars);
  mlx_loop(vars->mlx);
}
