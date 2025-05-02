/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitstream_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:55:01 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/02 19:19:51 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

/*LSB FIRST bitstream*/

uint64_t	bs_read_bits(t_bitstream *bs, int count)
{
	uint64_t	result;
	int			i;

	if (count <= 0 || count > 64)
		return (0);
	result = 0;
	i = 0;
	while (i < count)
	{
		if (bs->byte_pos >= bs->size)
		{
			bs->overflowed = true;
			return (0);
		}
		result |= (uint32_t)((bs->data[bs->byte_pos] >> bs->bit_pos) & 1) << i;
		bs->bit_pos++;
		if (bs->bit_pos == 8)
		{
			bs->bit_pos = 0;
			bs->byte_pos++;
		}
		i++;
	}
	return (result);
}

bool	bs_sread_64bits(t_bitstream *bs, int count, uint64_t *value)
{
	*value = (uint32_t) bs_read_bits(bs, count);
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
