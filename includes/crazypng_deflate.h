/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng_deflate.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:45:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/02 16:53:54 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_DEFLATE_H
# define CRAZYPNG_DEFLATE_H
# include "crazypng_utils.h"

# define LZ77_WINDOW_SIZE	32768

typedef struct s_lz77_window
{
	uint8_t		buffer[LZ77_WINDOW_SIZE];
	size_t		pos;
}	t_lz77_window;

typedef struct s_bitstream
{
	const uint8_t	*data;		// Pointeur vers les données compressées
	size_t			size;		// Taille totale
	size_t			byte_pos;	// Position dans le tableau de bytes
	uint8_t			bit_pos;	// Position du prochain bit (0 à 7)
	int				overflowed;
}	t_bitstream;

typedef struct s_inflate_context
{
	t_bitstream		bit_stream;
	t_lz77_window	reference_window;
	t_cp_buffer		*output;
	size_t			output_pos;
}	t_inflate_context;

uint32_t	read_bits(t_bitstream *bs, int count);
bool		cp_inflate(t_cp_buffer *output, uint8_t *input);

#endif