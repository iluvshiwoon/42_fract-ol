/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:03:53 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/28 19:22:45 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#include "minilibx-linux/mlx.h"
#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
# define FRACTOL_H
# include "42_MyLibC/mylibc.h"
#include <math.h>

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
} t_vars;

# endif
