/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:16 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/02 17:55:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static void	inflate_init_context(t_inflate_context *context, \
	t_cp_buffer *output, uint8_t *input, size_t length);
static bool	is_zlib_stream(t_bitstream *stream);

/*Deflate decompression algorithm*/

bool	cp_inflate(t_cp_buffer *output, uint8_t *input, size_t input_size)
{
	t_inflate_context	context;


	inflate_init_context(&context, output, input, input_size);
	if (!is_zlib_stream(&context.bit_stream))
		return (false);
	if (!inflate_read_blocks(&context))
		return (false);
	return (true);
}

static bool	inflate_read_blocks(t_inflate_context *context)
{
	int8_t		bfinal;
	int8_t		btype;

}

static void	inflate_init_context(t_inflate_context *context, \
	t_cp_buffer *output, uint8_t *input, size_t length)
{
	ft_memset(context, 0, sizeof(t_inflate_context));
	context->output = output;
	context->bit_stream.data = input;
	context->bit_stream.size = length;
}

static bool	is_zlib_stream(t_bitstream *stream)
{
	uint16_t	checksum;
	uint8_t		cmf;
	uint8_t		flg;

	cmf = read_bits(stream, 8);
	flg = read_bits(stream, 8);
	if (cmf == 0 || flg == 0 || stream->overflowed)
		return (false);
	if ((cmf & 0x0F) != 8 || flg & 0x20)
	{
		ft_putstr_fd(INFLATE_ERROR_UNSUPPORTED_METHOD, 2);
		return (false);
	}
	if((cmf >> 4) > 7)
	{
		ft_putstr_fd(INFLATE_ERROR_UNSUPPORTED_WINDOW, 2);
		return (false);
	}
	checksum = (cmf << 8) | flg;
	if (checksum % 31 != 0)
	{
		ft_putstr_fd(INFLATE_ERROR_CHECKSUM, 2);
		return (false);
	}
	return (true);
}
