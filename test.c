/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/29 17:49:48 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int close_win (int keycode, t_vars * vars)
{
    if (keycode == XK_Escape)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

int calc_mandelbrot(t_vars * vars)
{
    t_data img;
    int i;
    double zr;
    double zi;
    double zr_temp;

    vars->p_x = 0;
    vars->x = -1920./200;
    img.img = mlx_new_image(vars->mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (vars->p_x < 1920)
    {
        vars->p_y = 0;
        vars->y = -1080./200;
        while (vars->p_y < 1080)
        {
            i = 0;
            zr = 0.0;
            zi = 0.0;
            while (i < 50)
            {
                zr_temp = zr*zr - zi*zi + vars->x;
                zi = 2*zr*zi + vars->y;
                zr = zr_temp;
                if (zr*zr + zi*zi >= 4)
                    break;
                ++i;
            }
            if (i == 50)
                my_mlx_put_pixel(&img, vars->p_x, vars->p_y, create_trgb(0,0,0,0));
            else
                my_mlx_put_pixel(&img, vars->p_x, vars->p_y, create_trgb(0,(1*i)%255,(2*i)%255,(3*i)%255));
            ++(vars->p_y);
            vars->y += 0.01;
        }
        ++(vars->p_x);
        vars->x += 0.01;
    }
    mlx_put_image_to_window(vars->mlx, vars->win, &img, 0, 0);
    mlx_hook(vars->win, 2, 1L<<0, &close_win, vars);
    mlx_loop(vars->mlx);
    return 1;
}

int main(void)
{
    t_vars * vars;
    t_data img;

    vars = malloc(sizeof(*vars));
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "Mandelbrot");
    mlx_loop_hook(vars->mlx, &calc_mandelbrot, vars);
    mlx_loop(vars->mlx);
}
