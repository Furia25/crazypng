/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_chunk_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:22:05 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/23 00:23:45 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static int	chunk_read_header(t_png *png, t_png_chunk *chunk);

bool	png_chunk_read(t_png *png, t_png_chunk *chunk)
{
	chunk->data = NULL;
	if (!chunk_read_header(png, chunk))
		return (false);
	chunk->data = ft_calloc(sizeof(uint8_t), chunk->header.length);
	if (!chunk->data)
		return (false);
	if (cp_fread(chunk->data, sizeof(uint8_t),
			chunk->header.length, png->file) != chunk->header.length)
		return (false);
	if (cp_fread(&chunk->checksum, sizeof(uint32_t), 1, png->file) != 1)
		return (false);
	if (png->convert_endian)
		chunk->checksum = swap_endian32(chunk->checksum);
	return (true);
}

static int	chunk_read_header(t_png *png, t_png_chunk *chunk)
{
	uint32_t	buf[2];
	int			index;
	char		c;

	if (cp_fread(buf, sizeof(uint32_t), 2, png->file) != 2)
		return (false);
	if (png->convert_endian)
		buf[0] = swap_endian32(buf[0]);
	chunk->header.length = buf[0];
	chunk->header.type_code = buf[1];
	index = 0;
	while (index < 4)
	{
		c = chunk->header.type_str[index];
		if (!ft_isalpha(c))
			return (false);
		index++;
	}
	chunk->header.type_enum = png_chunk_get_type(chunk);
	return (true);
}
