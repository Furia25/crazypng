/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitstream_reads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:51:29 by val               #+#    #+#             */
/*   Updated: 2025/05/05 00:34:24 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

bool	bs_read_nbytes(t_bitstream *bs, t_cp_buffer *buffer, size_t len)
{
	if (len > SIZE_MAX / 8)
		return (false);
	if (bs->byte_pos + len > bs->size)
	{
		bs->overflowed = true;
		return (false);
	}
	if (!cp_buffer_add(buffer, &bs->data[bs->byte_pos], len))
		return (false);
	bs->byte_pos += len;
	bs->bit_pos = 0;
	return (true);
}

bool	bs_sread_64bits(t_bitstream *bs, int count, uint64_t *value)
{
	*value = bs_read_bits(bs, count);
	return (!bs->overflowed);
}

bool	bs_sread_32bits(t_bitstream *bs, int count, uint32_t *value)
{
	if (count > 32)
		return (false);
	*value = (uint32_t) bs_read_bits(bs, count);
	return (!bs->overflowed);
}

bool	bs_sread_16bits(t_bitstream *bs, int count, uint16_t *value)
{
	if (count > 16)
		return (false);
	*value = (uint16_t) bs_read_bits(bs, count);
	return (!bs->overflowed);
}

bool	bs_sread_8bits(t_bitstream *bs, int count, uint8_t *value)
{
	if (count > 8)
		return (false);
	*value = (uint8_t) bs_read_bits(bs, count);
	return (!bs->overflowed);
}
