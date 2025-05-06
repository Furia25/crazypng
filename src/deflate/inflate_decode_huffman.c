/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_decode_huffman.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:25:09 by val               #+#    #+#             */
/*   Updated: 2025/05/06 04:38:16 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static bool	length_from_symbol(int symbol, int *length, t_bitstream *stream);
static bool	distance_from_symbol(int symbol, int *dist, t_bitstream *stream);
static bool	handle_symbols(t_inflate_context *context, \
	t_bitstream *stream, int symbol, t_huffman_table *dist_table);

bool	inflate_block_huffman(t_inflate_context *context, \
	t_huffman_table *linlen, t_huffman_table *dist_table)
{
	t_bitstream	*stream;
	int			symbol;

	stream = &context->bit_stream;
	symbol = huffman_decode(stream, linlen);
	while (symbol > -1)
	{
		if (symbol == 256)
			return (true);
		if (symbol > 286)
			return (false);
		if (!handle_symbols(context, stream, symbol, dist_table))
			return (false);
		symbol = huffman_decode(stream, linlen);
	}
	return (false);
}

static bool	handle_symbols(t_inflate_context *context, \
	t_bitstream *stream, int symbol, t_huffman_table *dist_table)
{
	int			distance_symbol;
	int			length;
	int			distance;

	if (symbol < 256)
	{
		if (!cp_buffer_add(context->output, &symbol, 1))
			return (false);
		lz77_window_push(&context->reference_window, symbol);
	}
	else
	{
		if (!length_from_symbol(symbol, &length, stream))
			return (false);
		distance_symbol = huffman_decode(stream, dist_table);
		if (!distance_from_symbol(distance_symbol, &distance, stream))
			return (false);
		if (!inflate_copy_reference(context, distance, length))
			return (false);
	}
	return (true);
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

static bool	distance_from_symbol(int symbol, int *dist, t_bitstream *stream)
{
	t_code_info	info;
	uint16_t	temp;

	if (symbol < 0 || symbol > 29)
		return (false);
	temp = 0;
	info = g_deflate_distance_table[symbol];
	*dist = info.base;
	if (!bs_sread_16bits(stream, info.extra_bits, &temp))
		return (false);
	*dist += temp;
	return (true);
}
