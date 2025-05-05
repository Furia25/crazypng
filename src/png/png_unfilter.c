/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_filters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:49:35 by val               #+#    #+#             */
/*   Updated: 2025/05/06 01:35:35 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static bool	scanline_apply_filters(t_png_unfilter_context *context, t_png *png);

bool	png_unfilter(t_png *png)
{
	t_png_unfilter_context	context;

	context.y = 0;
	context.channels_number = channels_from_color(png->header.color_type);
	context.bits_pp = png->header.bit_depth * context.channels_number;
	context.lines_bytes = (png->header.width * (context.bits_pp) + 7) / 8;
	context.prev_line = ft_calloc(context.lines_bytes, 1);
	if (!context.prev_line)
		return (false);
	context.current_line = malloc(context.lines_bytes);
	if (!context.current_line)
	{
		free(context.prev_line);
		return (false);
	}
	if (!scanline_apply_filters(&context, png))
	{
		free(context.prev_line);
		free(context.current_line);
		return (false);
	}
	free(context.prev_line);
	free(context.current_line);
	return (true);
}

static bool	scanline_apply_filters(t_png_unfilter_context *context, t_png *png)
{
	int		filter_type;
	size_t	offset;
	uint8_t	*raw;
	uint8_t	*raw_line;

	raw = png->data.data;
	offset = 0;
	while (context->y < png->header.height)
	{
		filter_type = raw[offset];
		raw_line = raw + offset;
		offset += context->lines_bytes;
		if (filter_type == 0)
			ft_memcpy(context->current_line, raw_line, context->lines_bytes);
		else if (filter_type == 1)
			ft_putstr_fd("Sub", 2);
		else if (filter_type == 2)
			ft_putstr_fd("Up", 2);
		else if (filter_type == 3)
			ft_putstr_fd("Average", 2);
		else if (filter_type == 4)
			ft_putstr_fd("Paeth", 2);
		else
		{
			ft_putchar_fd("Png : Could not unfilter PNG decompressed data", 2);
			return (false);
		}
		scanline_bytes_to_pixels();
		swap_ptr(&context->current_line, &context->prev_line);
		context->y++;
	}
	return (true);
}
