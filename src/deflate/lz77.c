/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lz77.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:29:56 by val               #+#    #+#             */
/*   Updated: 2025/05/04 01:26:28 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

bool	lz77_window_push(t_lz77_window *win, uint8_t byte)
{
	win->buffer[win->pos] = byte;
	win->pos = (win->pos + 1) % LZ77_WINDOW_SIZE;
	return (true);
}

bool	lz77_window_push_bytes(t_lz77_window *win, \
	const uint8_t *src, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len)
	{
		win->buffer[win->pos] = src[index];
		win->pos = (win->pos + 1) % LZ77_WINDOW_SIZE;
		index++;
	}
	return (true);
}
