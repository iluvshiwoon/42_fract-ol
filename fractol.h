/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:03:53 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/03 21:12:18 by kgriset          ###   ########.fr       */
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

    double min_r;
    double max_r;

    double min_i;
    double max_i;

    int p_x;
    double offset_x;
    int p_y;
    double offset_y;
    double zoom;
    double x;
    double y;

    double center_r;
    double center_i;
    int is_pressed;
    char direction;
} t_vars;

int calc_mandelbrot(t_vars *vars);
double scale(char axe, double x, t_vars *vars);
# endif
