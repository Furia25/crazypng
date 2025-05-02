/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:16 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/02 16:54:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static void	inflate_init_context(t_inflate_context *context, \
	t_cp_buffer *output, uint8_t *input);

/*Deflate decompression algorithm*/

bool	cp_inflate(t_cp_buffer *output, uint8_t *input)
{
	t_inflate_context	context;

	inflate_init_context(&context, output, input);
	return (true);
}

static void	inflate_init_context(t_inflate_context *context, \
	t_cp_buffer *output, uint8_t *input)
{
	ft_memset(context, 0, sizeof(t_inflate_context));
	context->output = output;
	context->bit_stream.data = input;
}
