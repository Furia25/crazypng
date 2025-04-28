/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:13:16 by vdurand           #+#    #+#             */
/*   Updated: 2025/04/28 20:13:17 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_H
# define CRAZYPNG_H
# include <stdint.h>
# include <stdbool.h>

# define PNG_CHUNK_TYPE_CHAR_IHDR "IHDR"
# define PNG_CHUNK_TYPE_CHAR_IDAT "IDAT"
# define PNG_CHUNK_TYPE_CHAR_IEND "IEND"
# define PNG_CHUNK_TYPE_CHAR_PLTE "PLTE"

typedef enum e_png_chunk_type
{
	PNG_CHUNK_IHDR,
	PNG_CHUNK_IDAT,
	PNG_CHUNK_IEND,
	PNG_CHUNK_PLTE
}	t_png_chunk_type;

typedef enum e_png_color_type
{
	PNG_GRAYSCALE		= 0,
	PNG_RGB				= 2,
	PNG_PALETTE			= 3,
	PNG_ALPHA_GRAYSCALE = 4,
	PNG_RGBA			= 6
}	t_png_color_type;

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

typedef struct s_png_chunk_header
{
	uint32_t			length;
	t_png_chunk_type	type;
}	t_png_chunk_header;

typedef struct s_png_chunk
{
	t_png_chunk_header	header;
	uint8_t				*data;
	uint32_t			checksum;
}	t_png_chunk;

typedef struct s_png
{
	//	image_header
	uint32_t			width;
	uint32_t			height;
	uint8_t				bit_depth;
	t_png_color_type	color_type;
	bool				interlace;
	//
	u
}	t_png;

uint32_t	swap_endian(uint32_t value);

#endif