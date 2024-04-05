/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 10:36:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/05 11:45:26 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X11/X.h"
#include "fractol.h"

void	set_key_pressed(t_vars *vars, char direction)
{
	vars->direction = direction;
	move(vars);
	render(vars);
}

int	key_events(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		close_win(vars);
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		set_key_pressed(vars, 'D');
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		set_key_pressed(vars, 'A');
	else if (keycode == KEY_W || keycode == KEY_UP)
		set_key_pressed(vars, 'W');
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		set_key_pressed(vars, 'S');
	else if (keycode == KEY_PLUS)
		set_key_pressed(vars, '+');
	else if (keycode == KEY_MINUS)
		set_key_pressed(vars, '-');
	else if (keycode == KEY_J)
		shift_color(vars, 'J');
	else if (keycode == KEY_K)
		shift_color(vars, 'K');
	return (1);
}

static int	mouse_moved(t_vars *vars, int x, int y)
{
	if (vars->mouse_x == x && vars->mouse_y == y)
		return (0);
	return (1);
}

int	mouse_events(int keycode, int x, int y, t_vars *vars)
{
	if (keycode == Button4 | keycode == Button5 && mouse_moved(vars, x, y))
	{
		vars->mouse_x = x;
		vars->mouse_y = y;
		vars->offset_x += (double)x - VW / 2;
		vars->offset_y += (double)y - VH / 2;
	}
	if (keycode == Button4)
		set_key_pressed(vars, '+');
	if (keycode == Button5)
		set_key_pressed(vars, '-');
	return (1);
}
