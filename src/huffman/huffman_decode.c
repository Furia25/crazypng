/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:43:32 by val               #+#    #+#             */
/*   Updated: 2025/05/05 02:38:35 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "crazypng_huffman.h"
# include "crazypng_bitstream.h"

int	huffman_decode(t_bitstream *stream, t_huffman_table *tab)
{
	uint32_t	buf = bs_peek_bits(stream, tab->max_bits);

	for (size_t i = 0; i < tab->count; i++)
	{
		if (tab->codes[i].bits == 0)
			continue;
		uint8_t len = tab->codes[i].bits;
		uint32_t code = buf & ((1 << len) - 1);
		if (code == tab->codes[i].code)
		{
			if (!bs_consume_bits(stream, len))
				return -1;
			return i;
		}
	}
	return -1;
}
