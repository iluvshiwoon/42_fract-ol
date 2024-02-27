/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/27 12:49:19 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
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

int close_win (int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    return (1);
}

int main(void)
{
    t_vars vars;
    t_data img;
    int i;
    int j;

	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(vars.mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    i = 0;
    while (i < 1920)
    {
        j = 0;
        while (j < 1080)
        {
            my_mlx_put_pixel(&img, i, j, create_trgb(40,255,0,0));
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_hook(vars.win, 2, 1L<<0, &close_win, &vars);
	mlx_loop(vars.mlx);
}
