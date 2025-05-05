/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitstream_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:53:59 by val               #+#    #+#             */
/*   Updated: 2025/05/05 16:15:15 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

uint64_t	bs_peek_bits(t_bitstream *bs, int count)
{
	uint64_t	n;
	int			i;
	size_t		temp_byte_pos;
	int			temp_bit_pos;

	if (count <= 0 || count > 64 || bs->overflowed)
		return (0);
	n = 0;
	i = 0;
	temp_byte_pos = bs->byte_pos;
	temp_bit_pos = bs->bit_pos;
	while (i < count)
	{
		if (temp_byte_pos >= bs->size)
			return (0);
		n |= (uint64_t)((bs->data[temp_byte_pos] >> temp_bit_pos) & 1) << i;
		temp_bit_pos++;
		if (temp_bit_pos == 8)
		{
			temp_bit_pos = 0;
			temp_byte_pos++;
		}
		i++;
	}
	return (n);
}

bool	bs_consume_bits(t_bitstream *stream, size_t n)
{
	if (!stream || stream->overflowed)
		return (false);
	stream->bit_pos += n;
	while (stream->bit_pos >= 8)
	{
		stream->byte_pos++;
		stream->bit_pos -= 8;
	}
	if (stream->byte_pos >= stream->size)
	{
		stream->overflowed = true;
		return (false);
	}
	return (true);
}
