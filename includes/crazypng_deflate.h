/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng_deflate.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:45:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/23 00:20:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_DEFLATE_H
# define CRAZYPNG_DEFLATE_H
# include "crazypng_utils.h"
# include "crazypng_bitstream.h"
# include "crazypng_huffman.h"
# include "libft.h"

# define INFLATE_ERROR_UNSUPPORTED_METHOD	\
	"Decompression Error : Unsupported compression method\n"
# define INFLATE_ERROR_UNSUPPORTED_WINDOW	\
	"Decompression Error : Unsupported LZ77 window size\n"
# define INFLATE_ERROR_HEADER	\
	"Decompression Error : Invalid header\n"
# define INFLATE_ERROR_BLOCK	\
	"Decompression Error : Couldnt read block\n"

# define LZ77_WINDOW_SIZE	32768

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
	t_huffman_table	*huffman_fixed;
	t_huffman_table	*distance_fixed;
}	t_inflate_context;

# define DEFLATE_CLEN_SIZE	19
# define DEFLATE_CLEN_MAXBITS	7
# define DEFLATE_MAXBITS	15

typedef struct s_inflate_dynamic_data
{
	t_inflate_context	*context;
	uint16_t			temp_i;
	uint16_t			temp_size;
	uint8_t				temp_last;
	size_t				hlit;
	uint8_t				hdist;
	uint8_t				hclen;
	int					clen_tab[DEFLATE_CLEN_SIZE];
	t_huffman_table		clen_hufftable;
}	t_inflate_dynamic_data;

static const int			g_inflate_hclen_order[DEFLATE_CLEN_SIZE] = {
	16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
};

/*
** Tables de longueurs et de distances utilisées dans le décodage DEFLATE
** Voir RFC-1951 section 3.2.5
** https://www.rfc-editor.org/rfc/rfc1951.html#section-3.2.5
**
** Chaque symbole Huffman (longueur : 257–285, distance : 0–29) 
** correspond à une valeur (longueur minimale ou distance minimale)
** à laquelle il faut ajouter un nombre variable de bits
** supplémentaires lus depuis le flux compressé.
**
** Ces tables fournissent pour chaque symbole :
** - `base`       : valeur de base (longueur ou distance minimale)
** - `extra_bits` : nombre de bits supplémentaires à lire pour la valeur finale
**
** Exemple :
**   - 265 (longueur) correspond à une longueur de 11 et 1 bit supplémentaire.
**   - 4 (distance) correspond à une distance de 5 et 1 bit supplémentaire.
**
** Ces tables sont fixes et communes à tous les blocs DEFLATE, 
** qu'ils utilisent Huffman fixe ou dynamique.
*/

typedef struct s_code_info
{
	uint16_t	base;
	uint8_t		extra_bits;
}	t_code_info;

static const t_code_info	g_deflate_length_table[31] = {
{3, 0}, {4, 0}, {5, 0}, {6, 0},
{7, 0}, {8, 0}, {9, 0}, {10, 0},
{11, 1}, {13, 1}, {15, 1}, {17, 1},
{19, 2}, {23, 2}, {27, 2}, {31, 2},
{35, 3}, {43, 3}, {51, 3}, {59, 3},
{67, 4}, {83, 4}, {99, 4}, {115, 4},
{131, 5}, {163, 5}, {195, 5}, {227, 5},
{258, 0}, {0, 0}, {0, 0}
};

static const t_code_info	g_deflate_distance_table[30] = {
{1, 0}, {2, 0}, {3, 0}, {4, 0},
{5, 1}, {7, 1}, {9, 2}, {13, 2},
{17, 3}, {25, 3}, {33, 4}, {49, 4},
{65, 5}, {97, 5}, {129, 6}, {193, 6},
{257, 7}, {385, 7}, {513, 8}, {769, 8},
{1025, 9}, {1537, 9}, {2049, 10}, {3073, 10},
{4097, 11}, {6145, 11}, {8193, 12}, {12289, 12},
{16385, 13}, {24577, 13}
};

bool	lz77_window_push(t_lz77_window *win, uint8_t byte);
bool	lz77_window_push_bytes(t_lz77_window *win,
			const uint8_t *src, size_t len);

/*Inflate algorithm*/
bool	cp_inflate(t_cp_buffer *output, uint8_t *input, size_t input_size);

bool	inflate_block_uncompressed(t_inflate_context *context);
bool	inflate_block_huffman(t_inflate_context *context,
			t_huffman_table *linlen, t_huffman_table *distance);

bool	inflate_copy_reference(t_inflate_context *context,
			int distance, int length);
bool	inflate_get_dynamic(t_inflate_context *context,
			t_huffman_table **linlen, t_huffman_table **dist);

bool	read_dynamic_code_lengths(t_inflate_dynamic_data *data,
			t_huffman_table *clen_huff, int *code_lengths,
			uint16_t total_codes);

void	assign_huffman_codes(t_huffman_code *codes,
			const int *code_lengths, size_t count);

#endif