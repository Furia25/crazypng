/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:03:06 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/06 17:57:18 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_H
# define CRAZYPNG_H
# include <stdint.h>
# include "crazypng_utils.h"

typedef struct s_png_pixel8
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_png_pixel8;

typedef struct s_png_chunk_data_IHDR
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		bit_depth;
	uint8_t		color_type;
	uint8_t		compression;
	uint8_t		filter;
	uint8_t		interlace;
}	t_png_chunk_data_IHDR;

typedef struct s_png
{
	t_cp_file				*file;
	t_png_chunk_data_IHDR	header;
	t_cp_buffer				compressed_data;
	t_cp_buffer				data;
	t_png_pixel8			*pixels_8bit;
	t_png_pixel8			*palette;
	uint16_t				palette_size;
	bool					convert_endian;
	bool					animated;
}	t_png;

t_png	*png_open(char *file_name);
void	png_close(t_png *png);

#endif