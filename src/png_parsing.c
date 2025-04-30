/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:15:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/30 17:09:11 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static bool	png_parse_first(t_png *png, t_png_chunk *chunk);

bool	png_parse(t_png *png)
{
	t_png_chunk	chunk;

	if (!png_parse_first(png, &chunk))
		return (false);
	while (png_chunk_read(png, &chunk))
	{
		if (chunk.header.type_enum == PNG_CHUNK_IEND)
		{
			free(chunk.data);
			return (true);
		}
	}
	return (false);
}

static bool	png_parse_first(t_png *png, t_png_chunk *chunk)
{
	t_png_chunk_data_IHDR	ihdr;

	if (!png_chunk_read(png, chunk))
		return (false);
	if (chunk->header.type_enum != PNG_CHUNK_IHDR)
	{
		ft_putstr_fd("PNG Error: PNG not valid, first chunk must be IHDR\n", 2);
		return (false);
	}
	if (chunk->header.length != sizeof(t_png_chunk_data_IHDR))
	{
		ft_putstr_fd("PNG Error: Invalid IHDR size\n", 2);
		return  (false);
	}
	ft_memcpy(&ihdr, chunk->data, sizeof(t_png_chunk_data_IHDR));
	if (png->convert_endian)
	{
		ihdr.width = swap_endian32(ihdr.width);
		ihdr.height = swap_endian32(ihdr.height);
	}
	png->data.width = ihdr.width;
	png->data.height = ihdr.height;
	png->data.bit_depth = ihdr.bit_depth;
	png->data.color_type = ihdr.color_type;
	png->data. = ihdr.width;
	png->data.width = ihdr.width;
	return (true);
}
