/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazypng_png.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:42:30 by val               #+#    #+#             */
/*   Updated: 2025/04/30 00:42:30 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRAZYPNG_PNG_H
# define CRAZYPNG_PNG_H
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "crazypng_utils.h"

# define PNG_SIGNATURE	"\211PNG\r\n\032\n"

# define PNG_ERROR_SIGNATURE	"PNG Error: Wrong signature\n"
# define PNG_ERROR_BITDEPTH		"PNG Error: Invalid bit depth, color pair\n"
# define PNG_ERROR_IHDR_SIZE	"PNG Error: Invalid IHDR size\n"

# define PNG_CHUNK_SIZE_IHDR	13

# define PNG_CHUNK_TYPE_CHAR_IHDR "IHDR"
# define PNG_CHUNK_TYPE_CHAR_IDAT "IDAT"
# define PNG_CHUNK_TYPE_CHAR_IEND "IEND"
# define PNG_CHUNK_TYPE_CHAR_PLTE "PLTE"
# define PNG_CHUNK_TYPE_CHAR_GAMA "gAMA"

typedef enum e_png_chunk_type
{
	PNG_CHUNK_IHDR = 0,
	PNG_CHUNK_IDAT,
	PNG_CHUNK_IEND,
	PNG_CHUNK_PLTE,
	PNG_CHUNK_GAMA,
	PNG_CHUNK_UNKNOWN
}	t_png_chunk_type;

typedef enum e_png_color_type
{
	PNG_COLOR_GRAYSCALE			= 0,
	PNG_COLOR_RGB				= 2,
	PNG_COLOR_PALETTE			= 3,
	PNG_COLOR_ALPHA_GRAYSCALE	= 4,
	PNG_COLOR_RGBA				= 6
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
	uint32_t				length;
	t_png_chunk_type		type_enum;
	union
	{
		uint32_t			type_code;
		char				type_str[4];
	};
}	t_png_chunk_header;

typedef struct s_png_chunk
{
	t_png_chunk_header	header;
	bool				ancillary;
	bool				private;

	uint8_t				*data;
	uint32_t			checksum;
}	t_png_chunk;

typedef struct s_png
{
	t_cp_file				*file;
	t_png_chunk_data_IHDR	header;
	t_cp_buffer				uncompressed_data;
	t_cp_buffer				data;
	union
	{
		uint8_t		*pixels_8bit;
		uint16_t	*pixels_16bit;
	};
	uint32_t				*palette;
	uint32_t				palette_size;
	bool					convert_endian;
}	t_png;

bool				chunk_is_critical(t_png_chunk_type type);
bool				chunk_precede_idat(t_png_chunk_type type);
bool				chunk_precede_plte(t_png_chunk_type type);

bool				chunk_parse_ihdr(t_png *png, t_png_chunk *chunk);

t_png_chunk_type	png_chunk_get_type(t_png_chunk *chunk);
bool				png_chunk_read(t_png *png, t_png_chunk *chunk);
t_png				*png_open(char *file_name);
void				png_close(t_png *png);
bool				png_parse(t_png *png);
bool				png_decompress(t_png *png);

#endif