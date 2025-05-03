/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng_bitstream.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:55:13 by val               #+#    #+#             */
/*   Updated: 2025/05/03 23:56:42 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_BITSTREAM_H
# define CRAZYPNG_BITSTREAM_H

# include "crazypng_utils.h"

typedef struct s_bitstream
{
	uint8_t			*data;		// Pointeur vers les données compressées
	size_t			size;		// Taille totale
	size_t			byte_pos;	// Position dans le tableau de bytes
	uint8_t			bit_pos;	// Position du prochain bit (0 à 7)
	int				overflowed;
}	t_bitstream;

uint64_t	bs_peek_bits(t_bitstream *bs, int count);
bool		bs_consume_bits(t_bitstream *stream, size_t n);

uint64_t	bs_read_bits(t_bitstream *bs, int count);

bool		bs_read_nbytes(t_bitstream *bs, t_cp_buffer *buffer, size_t len);
bool		bs_sread_8bits(t_bitstream *bs, int count, uint8_t *value);
bool		bs_sread_16bits(t_bitstream *bs, int count, uint16_t *value);
bool		bs_sread_32bits(t_bitstream *bs, int count, uint32_t *value);
bool		bs_sread_64bits(t_bitstream *bs, int count, uint64_t *value);

bool		bs_align(t_bitstream *bs);
#endif