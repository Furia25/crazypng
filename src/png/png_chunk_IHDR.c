/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_chunk_IHDR.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:16:56 by val               #+#    #+#             */
/*   Updated: 2025/06/23 00:23:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static bool	is_valid_depthcolor_pair(uint8_t bit_depth, uint8_t color_type);

bool	chunk_parse_ihdr(t_png *png, t_png_chunk *chunk)
{
	if (chunk->header.length != PNG_CHUNK_SIZE_IHDR)
	{
		ft_putstr_fd(PNG_ERROR_IHDR_SIZE, 2);
		return (false);
	}
	ft_memcpy(&(png->header), chunk->data, PNG_CHUNK_SIZE_IHDR);
	if (!is_valid_depthcolor_pair(png->header.bit_depth,
			png->header.color_type))
	{
		ft_putstr_fd(PNG_ERROR_BITDEPTH, 2);
		return (false);
	}
	if (png->convert_endian)
	{
		png->header.width = swap_endian32(png->header.width);
		png->header.height = swap_endian32(png->header.height);
	}
	png->pixels_8bit = ft_calloc(png->header.width * png->header.height,
			sizeof(t_png_pixel8));
	if (!png->pixels_8bit)
		return (false);
	return (true);
}

static bool	is_valid_depthcolor_pair(uint8_t bit_depth, uint8_t color_type)
{
	if (bit_depth != 1 && bit_depth != 2 && bit_depth != 4
		&& bit_depth != 8 && bit_depth != 16)
		return (false);
	if (color_type != 0 && color_type != 2 && color_type != 3
		&& color_type != 4 && color_type != 6)
		return (false);
	if (color_type == 0)
		return (true);
	if (color_type == 2)
		return (bit_depth == 8 || bit_depth == 16);
	if (color_type == 3)
		return (bit_depth != 16);
	if (color_type == 4)
		return (bit_depth == 8 || bit_depth == 16);
	if (color_type == 6)
		return (bit_depth == 8 || bit_depth == 16);
	return (false);
}
