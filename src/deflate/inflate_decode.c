/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:03:37 by val               #+#    #+#             */
/*   Updated: 2025/05/04 03:36:40 by val              ###   ########.fr       */
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
	lz77_window_push_bytes(&context->reference_window, context->output->data + context->output->size - len, len);
	return (true);
}

bool	inflate_copy_reference(t_inflate_context *context, \
	int distance, int length)
{
	uint8_t	byte;
	size_t	temp_pos;
	int		index;

	temp_pos = (context->reference_window.pos - distance) % LZ77_WINDOW_SIZE;
	index = 0;
	while (index < length)
	{
		byte = context->reference_window.buffer[temp_pos];
		if (!cp_buffer_add(context->output, &byte, 1))
			return (false);
		lz77_window_push(&context->reference_window, byte);
		temp_pos = (temp_pos + 1) % LZ77_WINDOW_SIZE;
		index++;
	}
	return (true);
}

static bool	read_dynamic_hlengths(t_inflate_context *context, \
	t_inflate_dynamic_data *data);
static bool	init_dynamic_clen_tab(t_inflate_context *context, \
	t_inflate_dynamic_data *data);

bool	inflate_get_dynamic(t_inflate_context *context, \
	 t_huffman_table **linlen, t_huffman_table **dist)
{
	t_inflate_dynamic_data	data;

	if (!read_dynamic_hlengths(context, &data))
		return (false);
	if (!init_dynamic_clen_tab(context, &data))
		return (false);
}

static bool	read_dynamic_hlengths(t_inflate_context *context, \
	 t_inflate_dynamic_data *data)
{
	if (!bs_sread_8bits(&context->bit_stream, 5, &data->hlit))
		return (false);
	if (!bs_sread_8bits(&context->bit_stream, 5, &data->hdist))
		return (false);
	if (!bs_sread_8bits(&context->bit_stream, 4, &data->hclen))
		return (false);
	data->hlit += 257;
	data->hdist += 1;
	data->hclen += 4;
}

static bool	init_dynamic_clen_tab(t_inflate_context *context, \
	t_inflate_dynamic_data *data)
{
	uint8_t					index;
	uint8_t					temp;
	int						count;

	index = 0;
	count = 0;
	while (index < data->hclen)
	{
		temp = 0;
		if (!bs_sread_8bits(&context->bit_stream, 3, &temp))
			return (false);
		data->clen_tab[index] = temp;
		if (temp != 0)
			count++;
		index++;
	}
	data->clen_tab[index] = -1;
}
