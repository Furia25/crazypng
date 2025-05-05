/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:55:54 by val               #+#    #+#             */
/*   Updated: 2025/05/05 16:19:04 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_png.h"

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
