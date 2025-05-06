/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:16 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/06 17:58:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static bool	inflate_init_context(t_inflate_context *context, \
	t_cp_buffer *output, uint8_t *input, size_t length);
static bool	inflate_read_blocks(t_inflate_context *context);
static bool	is_zlib_stream(t_bitstream *stream);
static bool	handle_block_decompression(t_inflate_context *context, \
	uint8_t btype);

/**
 * @brief Décompresse des données DEFLATE
 * 
 * @param output Buffer de sortie pour les données décompressées
 * @param input Données compressées
 * @param input_size Taille des données compressées
 * @return true Décompression réussie
 * @return false Erreur pendant la décompression
 * 
 * @note Implémentation conforme au RFC 1951
 */
bool	cp_inflate(t_cp_buffer *output, uint8_t *input, size_t input_size)
{
	t_inflate_context	context;

	if (!inflate_init_context(&context, output, input, input_size))
		return (false);
	if (!is_zlib_stream(&context.bit_stream))
	{
		huffman_free_table(context.huffman_fixed);
		huffman_free_table(context.distance_fixed);
		return (false);
	}
	if (!inflate_read_blocks(&context))
	{
		ft_putstr_fd(INFLATE_ERROR_BLOCK, 2);
		huffman_free_table(context.huffman_fixed);
		huffman_free_table(context.distance_fixed);
		return (false);
	}
	huffman_free_table(context.huffman_fixed);
	huffman_free_table(context.distance_fixed);
	return (true);
}

static bool	inflate_init_context(t_inflate_context *context, \
	t_cp_buffer *output, uint8_t *input, size_t length)
{
	ft_memset(context, 0, sizeof(t_inflate_context));
	context->output = output;
	context->bit_stream.data = input;
	context->bit_stream.size = length;
	context->convert_endian = ft_isbigendian();
	context->huffman_fixed = huffman_deflate_table();
	if (!context->huffman_fixed)
		return (false);
	context->distance_fixed = huffman_deflate_dist_table();
	if (!context->distance_fixed)
		return (false);
	return (true);
}

static bool	inflate_read_blocks(t_inflate_context *context)
{
	uint8_t		bfinal;
	uint8_t		btype;
	bool		finished;

	finished = false;
	while (!finished)
	{
		if (!bs_sread_8bits(&context->bit_stream, 1, &bfinal))
			return (false);
		if (!bs_sread_8bits(&context->bit_stream, 2, &btype))
			return (false);
		finished = bfinal;
		if (!handle_block_decompression(context, btype))
			return (false);
	}
	return (true);
}

static bool	handle_block_decompression(t_inflate_context *context, \
	uint8_t btype)
{
	t_huffman_table	*dynamic_linlen;
	t_huffman_table	*dynamic_dist;
	bool			dynamic_result;

	if (btype == 0)
	{
		return (inflate_block_uncompressed(context));
	}
	else if (btype == 1)
	{
		return (inflate_block_huffman(context, context->huffman_fixed, \
			context->distance_fixed));
	}
	else if (btype == 2)
	{
		if (!inflate_get_dynamic(context, &dynamic_linlen, &dynamic_dist))
			return (false);
		dynamic_result = inflate_block_huffman(context, dynamic_linlen, \
			dynamic_dist);
		huffman_free_table(dynamic_linlen);
		huffman_free_table(dynamic_dist);
		return (dynamic_result);
	}
	else
		return (false);
}

static bool	is_zlib_stream(t_bitstream *stream)
{
	uint16_t	checksum;
	uint8_t		cmf;
	uint8_t		flg;

	cmf = bs_read_bits(stream, 8);
	flg = bs_read_bits(stream, 8);
	if (cmf == 0 || flg == 0 || stream->overflowed)
		return (false);
	if ((cmf & 0x0F) != 8 || flg & 0x20)
	{
		ft_putstr_fd(INFLATE_ERROR_UNSUPPORTED_METHOD, 2);
		return (false);
	}
	if ((cmf >> 4) > 7)
	{
		ft_putstr_fd(INFLATE_ERROR_UNSUPPORTED_WINDOW, 2);
		return (false);
	}
	checksum = (cmf << 8) | flg;
	if (checksum % 31 != 0)
	{
		ft_putstr_fd(INFLATE_ERROR_HEADER, 2);
		return (false);
	}
	return (true);
}
