/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitstream_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:55:01 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/06 17:58:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

/**
 * @brief Lit un nombre de bits depuis le flux
 * 
 * @param bs Flux binaire
 * @param count Nombre de bits à lire (1-64)
 * @return uint64_t Valeur lue
 * 
 * @warning Ne vérifie pas les dépassements de buffer
 */
uint64_t	bs_read_bits(t_bitstream *bs, int count)
{
	uint64_t	result;
	int			i;

	if (count <= 0 || count > 64 || bs->overflowed)
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

bool	bs_align(t_bitstream *bs)
{
	if (bs->bit_pos != 0)
	{
		bs->bit_pos = 0;
		bs->byte_pos += 1;
	}
	if (bs->byte_pos >= bs->size)
	{
		bs->overflowed = true;
		return (false);
	}
	return (true);
}
