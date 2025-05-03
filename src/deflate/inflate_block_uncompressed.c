/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_block_uncompressed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:03:37 by val               #+#    #+#             */
/*   Updated: 2025/05/03 15:39:53 by val              ###   ########.fr       */
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
	if ((len ^ nlen) != 0xFFFF)
		return (false);
	if (!bs_read_nbytes(bs, context->output, len))
		return (false);
	context->output_pos += len;
	lz77_window_push_bytes(&context->reference_window, \
		context->output->data + context->output_pos, len);
	return (true);
}
