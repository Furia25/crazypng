/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng_huffman.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:04:07 by val               #+#    #+#             */
/*   Updated: 2025/05/04 03:31:59 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_HUFFMAN_H
# define CRAZYPNG_HUFFMAN_H
# include "crazypng_utils.h"
# include "crazypng_bitstream.h"

# define DEFLATE_HUFFMAN_FIXED_SIZE	288

typedef struct s_huffman_code
{
	uint16_t	code;
	uint8_t		bits;
	uint16_t	value;
}	t_huffman_code;

typedef struct s_huffman_table
{
	t_huffman_code	*codes;
	size_t			count;
	uint16_t		max_bits;
}	t_huffman_table;

t_huffman_table	*huffman_deflate_table(void);
t_huffman_table	*huffman_deflate_dist_table(void);
t_huffman_table	*huffman_new_table(size_t count);
void			huffman_free_table(t_huffman_table *table);
int				huffman_decode(t_bitstream *stream, t_huffman_table *tab);

#endif