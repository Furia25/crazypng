/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:50:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/06 16:57:23 by vdurand          ###   ########.fr       */
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

typedef struct	s_img_data
{
	void *connection;
	void  *img;
	char  *buffer;
	int	  width;
	int   height;
	int   pbits;
	int   size_line;
	int   endian;
}               t_img_data;

int	argb_to_int(t_png_pixel8 argb)
{
	return (argb.a << 24 | argb.r << 16 | argb.g << 8 | argb.b);
}

void	img_draw_pixel(t_png_pixel8 argb, int x, int y, t_img_data *img)
{
	int	pixel;
	int	color;

	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return ;
	pixel = ((int) y * img->size_line) + ((int) x * 4);
	color = argb_to_int(argb);
	if (img->pbits != 32)
		color = mlx_get_color_value(img->connection, color);
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = (color >> 24);
		img->buffer[pixel + 1] = (color >> 16) & 0xFF;
		img->buffer[pixel + 2] = (color >> 8) & 0xFF;
		img->buffer[pixel + 3] = (color) & 0xFF;
	}
	else
	{
		img->buffer[pixel + 0] = (color) & 0xFF;
		img->buffer[pixel + 1] = (color >> 8) & 0xFF;
		img->buffer[pixel + 2] = (color >> 16) & 0xFF;
		img->buffer[pixel + 3] = (color >> 24);
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	t_png	*png;

	if (keycode == XK_space)
	{
		printf("ENDIANESS : %d\n", ft_isbigendian());
		png = png_open("test_files/16bitdepth.png");
		if (png)
		{
			printf(" SIZE : %ld\n", png->data.size);
		}
		else
		{
			perror("TEST");
			return 0;
		}
			
		t_img_data	img;
		img.connection = vars->mlx;
		img.img = mlx_new_image(vars->mlx, png->header.width, png->header.height);
		img.buffer = mlx_get_data_addr(img.img, &(img.pbits), &(img.size_line), &(img.endian));
		img.width = png->header.width;
		img.height = png->header.height;
		for (int y = 0; y < img.height; y++)
		{
			for (int x = 0; x < img.width; x++)
			{
				img_draw_pixel(png->pixels_8bit[y * img.width + x], x, y, &img);
			}
		}
		mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
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
	vars.win = mlx_new_window(vars.mlx, 1024, 1024, "PNG TEST");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
