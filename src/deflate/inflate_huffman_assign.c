/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_huffman_assign.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:46:04 by val               #+#    #+#             */
/*   Updated: 2025/06/23 00:32:04 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_deflate.h"

static void	count_code_lengths(const int *code_lengths,
				uint16_t *bl_count, size_t count);
static void	compute_first_codes(uint16_t *bl_count, uint16_t *next_code);

void	assign_huffman_codes(t_huffman_code *codes,
			const int *code_lengths, size_t count)
{
	uint16_t	bl_count[DEFLATE_MAXBITS + 1];
	uint16_t	next_code[DEFLATE_MAXBITS + 1];
	size_t		i;
	uint8_t		len;

	count_code_lengths(code_lengths, bl_count, count);
	compute_first_codes(bl_count, next_code);
	i = 0;
	while (i < count)
	{
		len = code_lengths[i];
		if (len != 0)
		{
			codes[i].code = reverse_32bits(next_code[len], len);
			codes[i].bits = len;
			next_code[len]++;
		}
		else
		{
			codes[i].code = 0;
			codes[i].bits = 0;
		}
		i++;
	}
}

static void	count_code_lengths(const int *code_lengths,
				uint16_t *bl_count, size_t count)
{
	size_t	i;

	i = 0;
	while (i <= DEFLATE_MAXBITS)
	{
		bl_count[i] = 0;
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (code_lengths[i] != 0)
			bl_count[code_lengths[i]]++;
		i++;
	}
}

static void	compute_first_codes(uint16_t *bl_count, uint16_t *next_code)
{
	uint16_t	code;
	int			bits;
	size_t		i;

	i = 0;
	while (i <= DEFLATE_MAXBITS)
	{
		next_code[i] = 0;
		i++;
	}
	code = 0;
	bits = 1;
	while (bits <= DEFLATE_MAXBITS)
	{
		code = (code + bl_count[bits - 1]) << 1;
		next_code[bits] = code;
		bits++;
	}
}
