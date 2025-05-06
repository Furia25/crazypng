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
# include "crazypng.h"

# define PNG_SIGNATURE	"\211PNG\r\n\032\n"

# define PNG_ERROR_SIGNATURE	"PNG Error: Wrong signature\n"
# define PNG_ERROR_BITDEPTH		"PNG Error: Invalid bit depth, color pair\n"
# define PNG_ERROR_IHDR_SIZE	"PNG Error: Invalid IHDR size\n"
# define PNG_ERROR_FILTERING_BUFFER	"PNG Error : Malformed buffer \
	during unfiltering\n"
# define PNG_ERROR_FILTERING_TYPE	"PNG Error : Could not unfilter \
	PNG decompressed data\n"

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
	PNG_COLOR_GRAYSCALE_ALPHA	= 4,
	PNG_COLOR_RGBA				= 6
}	t_png_color_type;

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

typedef struct s_png_unfilter_context
{
	size_t		y;
	size_t		lines_bytes;
	size_t		offset;
	size_t		bpp;
	size_t		bits_pp;
	uint8_t		bit_depths;
	uint8_t		channels_number;
	uint32_t	channel_max;
	uint8_t		*prev_line;
	uint8_t		*current_line;
	t_png		*png;
}	t_png_unfilter_context;

bool				chunk_precede_idat(t_png_chunk_type type);
bool				chunk_precede_plte(t_png_chunk_type type);
uint8_t				channels_from_color(t_png_color_type type);

bool				chunk_parse_ihdr(t_png *png, t_png_chunk *chunk);
bool				chunk_parse_plte(t_png *png, t_png_chunk *chunk,
						bool idat, int *plte);
t_png_chunk_type	png_chunk_get_type(t_png_chunk *chunk);
bool				png_chunk_read(t_png *png, t_png_chunk *chunk);

bool				png_parse(t_png *png);
bool				png_decompress(t_png *png);

bool				unpack_scanline_to_pixels(t_png_unfilter_context *context,
						t_png *png);
bool				png_unfilter(t_png *png);
/*Filters*/
void				png_filter_sub(t_png_unfilter_context *context,
						uint8_t *line);
void				png_filter_up(t_png_unfilter_context *context,
						uint8_t *line);
void				png_filter_average(t_png_unfilter_context *context,
						uint8_t *line);
void				png_filter_paeth(t_png_unfilter_context *context,
						uint8_t *line);

#endif