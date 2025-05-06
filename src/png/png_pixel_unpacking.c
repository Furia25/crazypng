/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_pixel_unpacking.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 04:03:37 by val               #+#    #+#             */
/*   Updated: 2025/05/06 04:35:48 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static void	unpack_pixel(t_png_unfilter_context *context, t_png_pixel8 *out, \
	size_t bitpos, size_t channel_n);
static bool	unpack_clean(t_png_unfilter_context *context, t_png_pixel8 *out);

bool	unpack_scanline_to_pixels(t_png_unfilter_context *context, \
	t_png *png)
{
	size_t			x;
	size_t			channel;
	size_t			bit_pos;
	t_png_pixel8	*out;

	out = png->pixels_8bit + png->header.width * context->y;
	x = 0;
	while (x < png->header.width)
	{
		bit_pos = x * context->channels_number * context->bit_depths;
		channel = 0;
		while (channel < context->channels_number)
		{
			unpack_pixel(context, out, bit_pos, channel);
			bit_pos += context->bit_depths;
			channel++;
		}
		if (!unpack_clean(context, out))
			return (false);
		out++;
		x++;
	}
	return (true);
}

static void	unpack_pixel(t_png_unfilter_context *context, t_png_pixel8 *out, \
	size_t bitpos, size_t channel_n)
{
	size_t		byte;
	size_t		offset;
	uint8_t		value;

	byte = bitpos >> 3;
	offset = bitpos & 7;
	value = context->current_line[byte];
	if (context->bit_depths < 8)
		value = ((value >> (8 - context->bit_depths - \
			offset)) & context->channel_max) * 255 / context->channel_max;
	if (channel_n == 0)
		out->r = value;
	else if (channel_n == 1)
		out->g = value;
	else if (channel_n == 2)
		out->b = value;
	else
		out->a = value;
}

static bool	unpack_clean(t_png_unfilter_context *context, t_png_pixel8 *out)
{
	t_png				*png;
	t_png_color_type	type;

	png = context->png;
	type = png->header.color_type;
	if (type == PNG_COLOR_GRAYSCALE)
		*out = (t_png_pixel8){out->r, out->r, out->r, 255};
	else if (type == PNG_COLOR_GRAYSCALE_ALPHA)
		*out = (t_png_pixel8){out->r, out->r, out->r, out->g};
	else if (type == PNG_COLOR_PALETTE)
	{
		//Handle palette
	}
	else if (type == PNG_COLOR_RGB)
		out->a = 255;
	return (true);
}
