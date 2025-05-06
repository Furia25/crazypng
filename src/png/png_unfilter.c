/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_unfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:49:35 by val               #+#    #+#             */
/*   Updated: 2025/05/06 03:43:57 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static bool	scanline_start(t_png_unfilter_context *context);
static bool	scanline_apply_filters(t_png_unfilter_context *context, \
	int filter_type);
static void	unpack_scanline_to_pixels(t_png_unfilter_context *context, \
	t_png *png);

bool	png_unfilter(t_png *png)
{
	t_png_unfilter_context	context;
	bool					result;

	context.png = png;
	context.y = 0;
	context.bit_depths = png->header.bit_depth;
	context.channels_number = channels_from_color(png->header.color_type);
	context.bits_pp = context.bit_depths * context.channels_number;
	context.bpp = (context.bits_pp + 7) / 8;;
	context.lines_bytes = ((png->header.width * context.bits_pp) + 7) / 8;
	context.prev_line = ft_calloc(context.lines_bytes, 1);
	if (!context.prev_line)
		return (false);
	context.current_line = malloc(context.lines_bytes);
	if (!context.current_line)
	{
		free(context.prev_line);
		return (false);
	}
	result = scanline_start(&context);
	free(context.prev_line);
	free(context.current_line);
	return (result);
}

static bool	scanline_start(t_png_unfilter_context *context)
{
	int		filter_type;
	t_png	*png;

	png = context->png;
	context->offset = 0;
	while (context->y < png->header.height)
	{
		if (context->offset + 1 + context->lines_bytes <= png->data.size)
		{
			ft_putstr_fd(PNG_ERROR_FILTERING_BUFFER, 2);
			return (false);
		}
		filter_type = png->data.data[context->offset];
		context->offset++;
		if (!scanline_apply_filters(context, filter_type))
			return (false);
		context->offset += context->lines_bytes;
		unpack_scanline_to_pixels(context);
		swap_ptr(&context->current_line, &context->prev_line);
		context->y++;
	}
	return (true);
}

static bool	scanline_apply_filters(t_png_unfilter_context *context, \
	int filter_type)
{
	size_t	bpp;
	uint8_t	*raw_line;

	raw_line = context->png->data.data + context->offset;
	if (filter_type == 0)
		ft_memcpy(context->current_line, raw_line, context->lines_bytes);
	else if (filter_type == 1)
		png_filter_sub(context, raw_line);
	else if (filter_type == 2)
		png_filter_up(context, raw_line);
	else if (filter_type == 3)
		png_filter_average(context, raw_line);
	else if (filter_type == 4)
		png_filter_paeth(context, raw_line);
	else
	{
		ft_putchar_fd(PNG_ERROR_FILTERING_TYPE, 2);
		return (false);
	}
	return (true);
}

static void	unpack_pixel(t_png_unfilter_context *context, t_png_pixel8 *out, \
	size_t bitpos, size_t channel_n);

static void	unpack_scanline_to_pixels(t_png_unfilter_context *context)
{
	t_png			*png;
	size_t			x;
	size_t			channel;
	size_t			bit_pos;
	t_png_pixel8	*out;

	png = context->png;
	out = png->pixels_8bit + png->header.width * context->y;
	context->channel_max = 
	x = 0;
	while (x < png->header.width)
	{
		bit_pos = x * channel * context->bit_depths;
		channel = 0;
		while (channel < context->channels_number)
		{
			unpack_pixel(context, out, bit_pos, channel);
			bit_pos += context->bit_depths;
			channel++;
		}
		if (channel <= 3)
			out->a = 255;
		out++;
		x++;
	}
}

static void	unpack_pixel(t_png_unfilter_context *context, t_png_pixel8 *out, \
	size_t bitpos, size_t channel_n)
{
	size_t		byte;
	size_t		offset;
	uint32_t	max_value;
	uint8_t		value;

	byte = bitpos >> 3;
	offset = bitpos & 7;
	max_value = (1 << context->bit_depths) - 1;
	if (context->bit_depths < 8)
		value = ((context->current_line[byte] >> \
			(8 - context->bit_depths - offset)) & max_value) * 255 \
			/ max_value;
	else
		value = context->current_line[byte];
	if (channel_n == 0)
		out->r = value;
	else if (channel_n == 1)
		out->g = value;
	else if (channel_n == 2)
		out->b = value;
	else
		out->a = value;
}
