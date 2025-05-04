/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_deflate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:48:50 by val               #+#    #+#             */
/*   Updated: 2025/05/04 19:33:27 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_huffman.h"

static void	set_huffman_code(t_huffman_code *ptr, uint16_t code, \
	bool is_bigendian, uint8_t bits);
static void	fill_literals(t_huffman_code *codes, bool is_bigendian);
static void	fill_lengths_and_eob(t_huffman_code *codes, bool is_bigendian);

t_huffman_table	*huffman_deflate_table(void)
{
	t_huffman_table	*table;
	bool			is_bigendian;

	table = huffman_new_table(DEFLATE_LL_TABLE_SIZE);
	if (!table)
		return (NULL);
	is_bigendian = ft_isbigendian();
	table->max_bits = 9;	
	fill_literals(table->codes, is_bigendian);
	fill_lengths_and_eob(table->codes + 256, is_bigendian);		
	return (table);
}

static void	fill_literals(t_huffman_code *codes, bool is_bigendian)
{
	size_t	i;

	i = 0;
	while (i < 144)
	{
		set_huffman_code(codes + i, 0x30 + i, is_bigendian, 8);
		i++;
	}
	while (i < 256)
	{
		set_huffman_code(codes + i, 0x190 + (i - 144), is_bigendian, 9);
		i++;
	}
}

static void	fill_lengths_and_eob(t_huffman_code *codes, bool is_bigendian)
{
	size_t	i;
	i = 0;

	set_huffman_code(codes + i, 0, is_bigendian, 7);
	i++;
	while (i < 24)
	{
		set_huffman_code(codes + i, i - 1, is_bigendian, 7);
		i++;
	}
	while (i < 32)
	{
		set_huffman_code(codes + i, 0xC0 + (i - 24), is_bigendian, 8);
		i++;
	}
}

t_huffman_table	*huffman_deflate_dist_table(void)
{
	t_huffman_table	*table;
	t_huffman_code	*temp;
	bool			is_bigendian;
	size_t			i;

	table = huffman_new_table(DEFLATE_D_TABLE_SIZE);
	if (!table)
		return (NULL);
	is_bigendian = ft_isbigendian();
	table->max_bits = 5;
	i = 0;
	temp = table->codes;
	while (i < DEFLATE_D_TABLE_SIZE)
	{
		set_huffman_code(temp + i, i, 5, is_bigendian);
		i++;
	}
	return (table);
}

static void	set_huffman_code(t_huffman_code *ptr, uint16_t code, \
	bool is_bigendian, uint8_t bits)
{
	ptr->bits = bits;
	if (is_bigendian)
		ptr->code = swap_endian16(code);
	else
		ptr->code = code;
}
