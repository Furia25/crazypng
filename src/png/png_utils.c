/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:37 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/06 03:58:53 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

t_png_chunk_type	png_chunk_get_type(t_png_chunk *chunk)
{
	char	*type_str;

	type_str = chunk->header.type_str;
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

bool	chunk_precede_plte(t_png_chunk_type type)
{
	return (type == PNG_CHUNK_GAMA);
}

bool	chunk_precede_idat(t_png_chunk_type type)
{
	return (type == PNG_CHUNK_IHDR || type == PNG_CHUNK_PLTE || \
			type == PNG_CHUNK_GAMA);
}

uint8_t	channels_from_color(t_png_color_type type)
{
	if (type == PNG_COLOR_RGB)
		return (3);
	if (type == PNG_COLOR_RGBA)
		return (4);
	if (type == PNG_COLOR_GRAYSCALE_ALPHA)
		return (2);
	if (type == PNG_COLOR_GRAYSCALE)
		return (1);
	if (type == PNG_COLOR_PALETTE)
		return (1);
	return (1);
}
