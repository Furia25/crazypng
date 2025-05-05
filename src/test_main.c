/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/05 15:51:55 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include "mlx_int.h"
#include "mlx.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	t_png	*png;

	if (keycode == XK_space)
	{
		printf("ENDIANESS : %d\n", ft_isbigendian());
		png = png_open("test_files/test4k.png");
		if (png)
		{
			printf(" SIZE : %ld\n", png->data.size);
		}
		else
			perror("TEST");
		png_close(png);
	}
	if (keycode == XK_Escape)
	{
		mlx_loop_end(vars->mlx);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (EXIT_FAILURE);
	vars.win = mlx_new_window(vars.mlx, 640, 480, "PNG TEST");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
