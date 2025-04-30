/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parsing_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:22:05 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/30 15:09:17 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

static int	png_chunk_read_header(t_png *png, t_png_chunk *chunk);
static t_png_chunk_type	png_chunk_get_type(char	type_str[4]);

bool	png_chunk_read(t_png *png, t_png_chunk *chunk)
{
	if (!png_chunk_read_header(png, chunk))
		return (false);
	chunk->data = ft_calloc(sizeof(uint8_t), chunk->header.length);
	if (!chunk->data)
		return (false);
	if (cp_fread(chunk->data, sizeof(uint8_t), \
		chunk->header.length, png->file) != chunk->header.length)
	 	return (false);
	if (cp_fread(&chunk->checksum, sizeof(uint32_t), 1, png->file) != 1)
		return (false);
	if (png->convert_endian)
		chunk->checksum = swap_endian32(chunk->checksum);
	return (true);
}

static int	png_chunk_read_header(t_png *png, t_png_chunk *chunk)
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
	chunk->header.type_enum = png_chunk_get_type(chunk->header.type_str);
	printf("%d", chunk->header.type_enum);
	return (true);
}

static t_png_chunk_type	png_chunk_get_type(char	type_str[4])
{
	if (ft_strncmp(type_str, PNG_CHUNK_TYPE_CHAR_IHDR, 3) == 0)
		return (PNG_CHUNK_IHDR);
	if (ft_strncmp(type_str, PNG_CHUNK_TYPE_CHAR_PLTE, 3) == 0)
		return (PNG_CHUNK_PLTE);
	if (ft_strncmp(type_str, PNG_CHUNK_TYPE_CHAR_IDAT, 3) == 0)
		return (PNG_CHUNK_IDAT);
	if (ft_strncmp(type_str, PNG_CHUNK_TYPE_CHAR_IEND, 3) == 0)
		return (PNG_CHUNK_IEND);
	if (ft_strncmp(type_str, PNG_CHUNK_TYPE_CHAR_GAMA, 3) == 0)
		return (PNG_CHUNK_GAMA);
	return (PNG_CHUNK_UNKNOWN);
}
