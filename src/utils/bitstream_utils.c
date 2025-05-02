/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitstream_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:55:01 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/02 16:05:57 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

/*LSB FIRST bitstream*/
uint32_t	read_bits(t_bitstream *bs, int count)
{
	uint32_t	result;
	int			i;

	if (count <= 0 || count > 32)
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
