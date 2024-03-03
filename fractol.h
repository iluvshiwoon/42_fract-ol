/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:03:53 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/03 21:09:40 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "minilibx-linux/mlx.h"
# include "42_MyLibC/mylibc.h"
# include <math.h>
# include "keycode.h"
#define VW 1920. / 2
#define VH 1080. / 2
#define PASS 50000

typedef struct s_data {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

typedef struct s_vars {
    void *mlx;
    void *win;
    int view_width;
    int view_height;

    long double min_r;
    long double max_r;

    long double min_i;
    long double max_i;

    int p_x;
    long double offset_x;
    int p_y;
    long double offset_y;
    long double zoom;
    long double x;
    long double y;

    long double center_r;
    long double center_i;
    int is_pressed;
    char direction;
} t_vars;

int calc_mandelbrot(t_vars *vars);
long double scale(char axe, long double x, t_vars *vars);
# endif
