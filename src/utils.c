/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:55:54 by val               #+#    #+#             */
/*   Updated: 2025/04/30 12:54:54 by vdurand          ###   ########.fr       */
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
		if (file->pos >= file->valid_bytes)
		{
			file->valid_bytes = read(file->fd, file->buffer, CP_BUFFER_SIZE);
			if (file->valid_bytes == 0)
				return (copied / size);
			if (file->valid_bytes == (size_t) - 1)
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
