/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:43:32 by val               #+#    #+#             */
/*   Updated: 2025/05/03 22:17:46 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "crazypng_huffman.h"
# include "crazypng_bitstream.h"

int	huffman_decode(t_bitstream *stream, t_huffman_table *tab)
{
	uint32_t	buf;
	uint16_t	mask;
	size_t		y;
	size_t		i;

	buf = bs_peek_bits(stream, tab->max_bits);
	y = 0;
	i = 0;
	while (y < tab->max_bits)
	{
		y++;
		mask = (1 << y) - 1;
		while (i < tab->count)
		{
			if ((buf & mask) == tab->codes[i].code && y == tab->codes[i].bits)
			{
				if (!bs_consume_bits(stream, y))
					return (-1);
				return (i);
			}
			i++;
		}
		i = 0;
	}
	return (-1);
}
