/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:15:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/06 18:05:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static bool	chunk_parse_idat(t_png *png, t_png_chunk *chunk, bool *encountered);
static bool	png_chunk_end(t_png *png, t_png_chunk *chunk, bool idat, int plte);
static bool	png_parse_first(t_png *png, t_png_chunk *chunk);
static int	chunk_return(t_png_chunk *chunk, int return_code);

bool	png_parse(t_png *png)
{
	int				plte_number;
	bool			idat;
	bool			result;
	t_png_chunk		chunk;

	idat = false;
	plte_number = 0;
	result = true;
	if (!png_parse_first(png, &chunk))
		return (chunk_return(&chunk, false));
	while (png_chunk_read(png, &chunk))
	{
		if (chunk_precede_idat(chunk.header.type_enum) && idat)
			return (chunk_return(&chunk, false));
		if (chunk.header.type_enum == PNG_CHUNK_IEND)
			return (png_chunk_end(png, &chunk, idat, plte_number));
		if (chunk.header.type_enum == PNG_CHUNK_PLTE)
			result = chunk_parse_plte(png, &chunk, idat, &plte_number);
		else if (chunk.header.type_enum == PNG_CHUNK_IDAT)
			result = chunk_parse_idat(png, &chunk, &idat);
		if (!result)
			return (chunk_return(&chunk, false));
		free(chunk.data);
	}
	return (chunk_return(&chunk, false));
}

static bool	chunk_parse_idat(t_png *png, t_png_chunk *chunk, bool *encountered)
{
	if (!cp_buffer_add(&png->compressed_data, chunk->data, \
		chunk->header.length))
		return (false);
	*encountered = true;
	return (true);
}

static bool	png_chunk_end(t_png *png, t_png_chunk *chunk, bool idat, int plte)
{
	if (chunk->data)
		free(chunk->data);
	if (!idat)
		return (false);
	if (plte == 1)
	{
		if (!(png->header.color_type == PNG_COLOR_PALETTE || \
			png->header.color_type == PNG_COLOR_RGB || \
			png->header.color_type == PNG_COLOR_RGBA))
			return (false);
	}
	else if (plte == 0 && png->header.color_type == PNG_COLOR_PALETTE)
		return (false);
	else if (plte > 1)
		return (false);
	if (!png_decompress(png))
		return (false);
	if (!png_unfilter(png))
		return (false);
	cp_buffer_reset(&png->compressed_data);
	cp_buffer_reset(&png->data);
	return (true);
}

static bool	png_parse_first(t_png *png, t_png_chunk *chunk)
{
	if (!png_chunk_read(png, chunk))
		return (false);
	if (chunk->header.type_enum != PNG_CHUNK_IHDR)
	{
		ft_putstr_fd("PNG Error: PNG not valid, first chunk must be IHDR\n", 2);
		return (false);
	}
	if (!chunk_parse_ihdr(png, chunk))
		return (false);
	free(chunk->data);
	return (true);
}

static int	chunk_return(t_png_chunk *chunk, int return_code)
{
	if (chunk->data)
		free(chunk->data);
	return (return_code);
}
