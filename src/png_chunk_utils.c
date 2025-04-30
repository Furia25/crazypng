/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_chunk_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:37 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/30 15:38:26 by vdurand          ###   ########.fr       */
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

bool	png_ischunk_critical(t_png_chunk_type type)
{
	return (type == PNG_CHUNK_IHDR || type == PNG_CHUNK_PLTE || \
			type == PNG_CHUNK_IDAT || type == PNG_CHUNK_IEND);
}
