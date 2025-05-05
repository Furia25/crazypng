/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:43:32 by val               #+#    #+#             */
/*   Updated: 2025/05/05 16:54:22 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_huffman.h"
#include "crazypng_bitstream.h"

int	huffman_decode(t_bitstream *stream, t_huffman_table *tab)
{
	uint32_t	buf;
	uint8_t		len;
	uint32_t	code;
	size_t		i;

	i = 0;
	buf = bs_peek_bits(stream, tab->max_bits);
	while (i < tab->count)
	{
		if (tab->codes[i].bits == 0)
		{
			i++;
			continue ;
		}
		len = tab->codes[i].bits;
		code = buf & ((1 << len) - 1);
		if (code == tab->codes[i].code)
		{
			if (!bs_consume_bits(stream, len))
				return (-2);
			return (i);
		}
		i++;
	}
	return (-1);
}
