/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/28 19:39:29 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef struct s_pos {
    void * mlx;
    void * win;
    int a;
    int b;
} t_pos;

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
    if (keycode == XK_Escape)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

int change_pos (int keycode, t_pos * pos)
{
    if (keycode == XK_w)
        pos->a += 1;
    return 1;
}

int render_next_frame(t_pos * pos)
{
    int i;
    int j;
    t_data img;

    img.img = mlx_new_image(pos->mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    i = 0;
    while (i < 1000)
    {
        j = 0;
        while (j < 1000)
        {
            if (pow((double)i - pos->a,2) + pow((double)j - pos->b,2) < 500)
                my_mlx_put_pixel(&img, i, j, create_trgb(40,255,0+i%255,0));
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(pos->mlx, pos->win, img.img, 400, 400);
    mlx_hook(pos->win, 2, 1L<<0, &change_pos, pos);
    mlx_hook(pos->win, 2, 1L<<0, &close_win, pos);
    mlx_loop(pos->mlx);
    return 1;
}

int main(void)
{
    t_vars vars;
    t_data img;
    t_pos * pos;
    int i;
    int j;

    pos = malloc(sizeof(*pos));
    pos->a = 200;
    pos->b = 200;
	vars.mlx = mlx_init();
    pos->mlx = vars.mlx;

	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "test!");
    pos->win = vars.win;
    img.img = mlx_new_image(vars.mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    mlx_loop_hook(vars.mlx, &render_next_frame, pos);
	mlx_loop(vars.mlx);
}
