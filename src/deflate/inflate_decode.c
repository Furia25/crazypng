/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:03:37 by val               #+#    #+#             */
/*   Updated: 2025/05/04 00:51:57 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

bool	inflate_block_uncompressed(t_inflate_context *context)
{
	uint16_t	len;
	uint16_t	nlen;
	t_bitstream	*bs;

	bs = &context->bit_stream;
	if (!bs_align(bs))
		return (false);
	if (!bs_sread_16bits(bs, 16, &len) || !bs_sread_16bits(bs, 16, &nlen))
		return (false);
	if (context->convert_endian)
	{
		len = swap_endian16(len);
		nlen = swap_endian16(nlen);
	}
	if ((len ^ nlen) != 0xFFFF)
		return (false);
	if (!bs_read_nbytes(bs, context->output, len))
		return (false);
	context->output_pos += len;
	lz77_window_push_bytes(&context->reference_window, \
		context->output->data + context->output_pos, len);
	return (true);
}

static bool	length_from_symbol(int symbol, int *length, t_bitstream *stream);
static bool	distance_from_symbol(int symbol, int *distance, t_bitstream *stream);

bool	inflate_block_huffman(t_inflate_context *context, \
	t_huffman_table *linlen, t_huffman_table *dist_table)
{
	t_bitstream	*stream;
	int			symbol;
	int			distance_symbol;
	int			length;
	int			distance;

	stream = &context->bit_stream;
	symbol = huffman_decode(stream, linlen);
	while (symbol > -1)
	{
		if (symbol == 256)
			return (true);
		if (symbol > 286)
			return (false);
		if (symbol < 256)
		{
			if (!cp_buffer_add(context->output, &symbol, 1))
				return (false);
			context->output_pos += 1;
			lz77_window_push(&context->reference_window, symbol);
		}
		else
		{
			if (!length_from_symbol(symbol, &length, stream))
			return (false);
			distance_symbol = huffman_decode(stream, dist_table);
			if (!distance_from_symbol(distance_symbol, &distance, stream))
				return (false);
		}
		symbol = huffman_decode(stream, linlen);
	}
	return (false);
}

/*Petit soucis d'endianess possible*/

static bool	length_from_symbol(int symbol, int *length, t_bitstream *stream)
{
	t_code_info	info;
	uint16_t	temp;

	temp = 0;
	info = g_deflate_length_table[symbol - 257];
	*length = info.base;
	if (!bs_sread_16bits(stream, info.extra_bits, &temp))
		return (false);
	*length += temp;
	return (true);
}

static bool	distance_from_symbol(int symbol, int *distance, t_bitstream *stream)
{
	t_code_info	info;
	uint16_t	temp;

	if (symbol < 0 || symbol > 29)
		return (false);
	temp = 0;
	info = g_deflate_distance_table[symbol];
	*distance = info.base;
	if (!bs_sread_16bits(stream, info.extra_bits, &temp))
		return (false);
	*distance += temp;
	return (true);
}
