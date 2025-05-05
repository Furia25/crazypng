/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:27:15 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/05 15:46:31 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_utils.h"

bool	cp_buffer_add(t_cp_buffer *buf, void *to_add, size_t len)
{
	size_t	new_capacity;
	uint8_t	*new_data;

	new_capacity = buf->capacity;
	if (buf->size + len > buf->capacity)
	{
		if (new_capacity < 1024)
			new_capacity = 1024;
		while (new_capacity < buf->capacity + len)
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
	ft_memcpy(buf->data + buf->size, to_add, len);
	buf->size += len;
	return (true);
}

void	cp_buffer_free(t_cp_buffer *buffer)
{
	cp_buffer_reset(buffer);
	free(buffer);
}

void	cp_buffer_reset(t_cp_buffer *buffer)
{
	if (buffer->data)
	{
		free(buffer->data);
		buffer->data = NULL;
	}
	buffer->size = 0;
	buffer->capacity = 0;
}
