/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:15:41 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/30 15:39:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static bool	png_parse_first(t_png *png, t_png_chunk *chunk);

bool	png_parse(t_png *png)
{
	t_png_chunk	chunk;

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
	if (!png_chunk_read(png, chunk))
		return (false);
	if (chunk->header.type_enum != PNG_CHUNK_IHDR)
		return (false);
}
