/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_chunk_PLTE.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:47:27 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/23 01:13:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static void	parse_palette_entries(t_png *png, t_png_chunk *chunk);

bool	chunk_parse_plte(t_png *png, t_png_chunk *chunk, bool idat, int *plte)
{
	size_t	entries;

	if (idat || *plte > 0)
		return (false);
	if (png->header.color_type == PNG_COLOR_GRAYSCALE
		|| png->header.color_type == PNG_COLOR_GRAYSCALE_ALPHA)
		return (false);
	if (chunk->header.length % 3 != 0)
		return (false);
	entries = chunk->header.length / 3;
	if (entries > (size_t)(1 << png->header.bit_depth))
		return (false);
	png->palette_size = entries;
	png->palette = ft_calloc(entries, sizeof(t_png_pixel8));
	if (!png->palette)
		return (false);
	parse_palette_entries(png, chunk);
	(*plte)++;
	return (true);
}

static void	parse_palette_entries(t_png *png, t_png_chunk *chunk)
{
	size_t			entry;
	uint8_t			*data_byte;
	t_png_pixel8	*entry_pixel;

	entry = 0;
	data_byte = chunk->data;
	while (entry < png->palette_size)
	{
		entry_pixel = png->palette + entry;
		entry_pixel->r = data_byte[0];
		entry_pixel->g = data_byte[1];
		entry_pixel->b = data_byte[2];
		entry_pixel->a = 255;
		data_byte += 3;
		entry++;
	}
}
