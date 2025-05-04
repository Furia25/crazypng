/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:55:54 by val               #+#    #+#             */
/*   Updated: 2025/05/04 22:38:44 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

t_cp_file	*cp_open(char *name, int flags)
{
	t_cp_file	*file;

	file = malloc(sizeof(t_cp_file));
	if (!file)
		return (NULL);
	file->fd = open(name, flags);
	if (file->fd == -1)
	{
		free(file);
		return (NULL);
	}
	file->valid_bytes = 0;
	file->pos = 0;
	return (file);
}

void	cp_close(t_cp_file *file)
{
	if (file)
	{
		if (file->fd != -1)
			close(file->fd);
		free(file);
	}
}

size_t	cp_fread(void *ptr, size_t size, size_t nmemb, t_cp_file *file)
{
	size_t	total_bytes;
	size_t	copied;
	size_t	to_copy;

	total_bytes = size * nmemb;
	copied = 0;
	while (copied < total_bytes)
	{
		if (file->pos >= (size_t) file->valid_bytes)
		{
			file->valid_bytes = read(file->fd, file->buffer, CP_BUFFER_SIZE);
			if (file->valid_bytes == 0)
				return (copied / size);
			if (file->valid_bytes == -1)
				return (0);
			file->pos = 0;
		}
		to_copy = file->valid_bytes - file->pos;
		if (to_copy > total_bytes - copied)
			to_copy = total_bytes - copied;
		ft_memcpy((char *)ptr + copied, file->buffer + file->pos, to_copy);
		file->pos += to_copy;
		copied += to_copy;
	}
	return (nmemb);
}

uint32_t	swap_endian32(uint32_t value)
{
	return (((value >> 24) & 0xFF) | ((value >> 8) & 0xFF00) | \
		((value << 8) & 0xFF0000) | ((value << 24) & 0xFF000000));
}

uint16_t	swap_endian16(uint16_t value)
{
	return ((value >> 8) | (value << 8));
}

uint64_t	reverse_64bits(uint64_t x, int bits)
{
	x = ((x >> 1) & 0x5555555555555555ULL) | ((x & 0x5555555555555555ULL) << 1);
	x = ((x >> 2) & 0x3333333333333333ULL) | ((x & 0x3333333333333333ULL) << 2);
	x = ((x >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((x & 0x0F0F0F0F0F0F0F0FULL) << 4);
	x = ((x >> 8) & 0x00FF00FF00FF00FFULL) | ((x & 0x00FF00FF00FF00FFULL) << 8);
	x = ((x >> 16) & 0x0000FFFF0000FFFFULL) | ((x & 0x0000FFFF0000FFFFULL) << 16);
	x = (x >> 32) | (x << 32);
	return x >> (64 - bits);
}

uint32_t	reverse_bits32(uint32_t code, int len)
{
	uint32_t reversed = 0;
	for (int i = 0; i < len; i++) {
		reversed = (reversed << 1) | (code & 1);
		code >>= 1;
	}
	return reversed;
}
