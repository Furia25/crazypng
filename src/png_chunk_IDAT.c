/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_chunk_IDAT.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:59:48 by val               #+#    #+#             */
/*   Updated: 2025/05/01 16:33:56 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

bool	chunk_idat_add(t_png_deflate_data *buf, t_png_chunk *chunk)
{
	size_t	new_capacity;
	uint8_t	*new_data;

	new_capacity = buf->capacity;
	if (buf->size + chunk->header.length > buf->capacity)
	{
		if (new_capacity < 1024)
			new_capacity = 1024;
		while (new_capacity < buf->capacity + chunk->header.length)
			new_capacity *= 2;
		new_data = malloc(new_capacity);
		if (!new_data)
			return (false);
		if (buf->data)
		{
			ft_memcpy(new_data, buf->data, buf->size);
			free(buf->data);
		}
		buf->data = new_data;
		buf->capacity = new_capacity;
	}
	ft_memcpy(buf->data + buf->size, chunk->data, chunk->header.length);
	buf->size += chunk->header.length;
	return (true);
}
