/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_deflate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:48:50 by val               #+#    #+#             */
/*   Updated: 2025/05/05 16:54:48 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "crazypng_huffman.h"

static void	set_huffman_code(t_huffman_code *ptr, uint16_t code, uint8_t bits);
static void	fill_literals(t_huffman_code *codes);
static void	fill_lengths_and_eob(t_huffman_code *codes);

t_huffman_table	*huffman_deflate_table(void)
{
	t_huffman_table	*table;

	table = huffman_new_table(DEFLATE_LL_TABLE_SIZE);
	if (!table)
		return (NULL);
	table->max_bits = 9;
	fill_literals(table->codes);
	fill_lengths_and_eob(table->codes + 256);
	return (table);
}

static void	fill_literals(t_huffman_code *codes)
{
	size_t	i;

	i = 0;
	while (i < 144)
	{
		set_huffman_code(codes + i, 0x30 + i, 8);
		i++;
	}
	while (i < 256)
	{
		set_huffman_code(codes + i, 0x190 + (i - 144), 9);
		i++;
	}
}

static void	fill_lengths_and_eob(t_huffman_code *codes)
{
	size_t	i;

	i = 0;
	set_huffman_code(codes + i, 0, 7);
	i++;
	while (i < 24)
	{
		set_huffman_code(codes + i, i - 1, 7);
		i++;
	}
	while (i < 32)
	{
		set_huffman_code(codes + i, 0xC0 + (i - 24), 8);
		i++;
	}
}

t_huffman_table	*huffman_deflate_dist_table(void)
{
	t_huffman_table	*table;
	t_huffman_code	*temp;
	size_t			i;

	table = huffman_new_table(DEFLATE_D_TABLE_SIZE);
	if (!table)
		return (NULL);
	table->max_bits = 5;
	i = 0;
	temp = table->codes;
	while (i < DEFLATE_D_TABLE_SIZE)
	{
		set_huffman_code(temp + i, i, 5);
		i++;
	}
	return (table);
}

static void	set_huffman_code(t_huffman_code *ptr, uint16_t code, uint8_t bits)
{
	ptr->bits = bits;
	ptr->code = code;
}
