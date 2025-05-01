/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:15:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/01 16:34:30 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static bool	png_parse_first(t_png *png, t_png_chunk *chunk);
static int	chunk_return(t_png_chunk *chunk, int return_code);

bool	png_parse(t_png *png)
{
	bool			idat_encountered;
	t_png_chunk		chunk;

	idat_encountered = false;
	if (!png_parse_first(png, &chunk))
		return (chunk_return(&chunk, false));
	while (png_chunk_read(png, &chunk))
	{
		if (chunk_precede_idat(chunk.header.type_enum) && idat_encountered)
			return (chunk_return(&chunk, false));
		if (chunk.header.type_enum == PNG_CHUNK_IEND)
			return (chunk_return(&chunk, idat_encountered));
		if (chunk.header.type_enum == PNG_CHUNK_IDAT)
		{
			if (!chunk_idat_add(&png->uncompressed_data, &chunk))
				return (chunk_return(&chunk, false));
			idat_encountered = true;
		}
		free(chunk.data);
	}
	return (chunk_return(&chunk, false));
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
