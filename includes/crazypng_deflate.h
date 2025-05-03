/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng_deflate.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:45:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/03 21:13:31 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_DEFLATE_H
# define CRAZYPNG_DEFLATE_H
# include "crazypng_utils.h"
# include "crazypng_bitstream.h"
# include "crazypng_huffman.h"

# define INFLATE_ERROR_UNSUPPORTED_METHOD	\
	"Decompression Error : Unsupported compression method\n"
# define INFLATE_ERROR_UNSUPPORTED_WINDOW	\
	"Decompression Error : Unsupported LZ77 window size\n"
# define INFLATE_ERROR_CHECKSUM	\
	"Decompression Error : Invalid header checksum\n"

# define LZ77_WINDOW_SIZE	32768

# define DEFLATE_HUFFMAN_FIXED_SIZE	288

typedef struct s_lz77_window
{
	uint8_t		buffer[LZ77_WINDOW_SIZE];
	size_t		pos;
}	t_lz77_window;

typedef struct s_inflate_context
{
	bool			convert_endian;
	t_bitstream		bit_stream;
	t_lz77_window	reference_window;
	t_cp_buffer		*output;
	size_t			output_pos;
	t_huffman_table	*huffman_fixed;
	t_huffman_table	*distance_fixed;
}	t_inflate_context;

bool	lz77_window_push(t_lz77_window *win, uint8_t byte);
bool	lz77_window_push_bytes(t_lz77_window *win, \
	const uint8_t *src, size_t len);

/*Inflate algorithm*/
bool	cp_inflate(t_cp_buffer *output, uint8_t *input, size_t input_size);

bool	inflate_block_uncompressed(t_inflate_context *context);
bool	inflate_block_fixed(t_inflate_context *context);
bool	inflate_block_dynamic(t_inflate_context *context);

#endif